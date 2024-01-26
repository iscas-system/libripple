// Copyright (c) 2023 Institute of Software, Chinese Academy of Sciences
// libripple is licensed under Mulan PSL v2.
// You can use this software according to the terms and conditions of the Mulan PSL v2.
// You may obtain a copy of Mulan PSL v2 at:
//          http://license.coscl.org.cn/MulanPSL2
// THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
// EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
// MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
// See the Mulan PSL v2 for more details.

#include "MessageService.h"
#include <uuid/uuid.h>
#include <memory>

// TODO: Implement this
namespace Ripple {
    namespace Common {
        namespace Storage {
            MessageService::MessageService(Storage *storage) {
                this->storage = storage;
            }

            MessageService::~MessageService() {

            }

            bool MessageService::NewMessage(std::shared_ptr<Entity::AbstractMessage> message) {
                if (Entity::UpdateMessage *updateMessage = dynamic_cast<Entity::UpdateMessage *>(message.get())) {
                    return this->NewUpdateMessage(updateMessage);
                } else if (Entity::DeleteMessage *deleteMessage = dynamic_cast<Entity::DeleteMessage *>(message.get())) {
                    return this->NewDeleteMessage(deleteMessage);
                } else if (Entity::IncrementalUpdateMessage *incrementalUpdateMessage = dynamic_cast<Entity::IncrementalUpdateMessage *>(message.get())) {
                    return this->NewIncrementalUpdateMessage(incrementalUpdateMessage);
                }
                return false;
            }

            bool MessageService::Exist(const uuid_t messageUuid) {
                bool ret = false;
                const char *sql = "SELECT * FROM [message] WHERE [uuid] = ?;";
                sqlite3_stmt *statement = nullptr;
                if (sqlite3_prepare_v2(this->storage->GetDataBase(), sql, -1, &statement, nullptr) == SQLITE_OK) {
                    char uuidString[37]= {0};
                    uuid_unparse(messageUuid, uuidString);
                    sqlite3_bind_text(statement, 1, uuidString, -1, nullptr);

                    int step = sqlite3_step(statement);
                    if (step == SQLITE_ROW) {
                        ret = true;
                    }
                    sqlite3_finalize(statement);
                }
                return ret;
            }

            bool MessageService::NewUpdateMessage(Entity::UpdateMessage *updateMessage) {
                if (this->Exist(updateMessage->GetUuid())) {
                    return false;
                }

                const char *sql = "INSERT INTO [message] "
                                  "([uuid], [item_application_name], [item_key], "
                                  "[message_type], [new_value], [last_update], [last_update_id]) "
                                  "VALUES (?,?,?,?,?,?,?);";
                sqlite3_stmt *statement = nullptr;
                if (sqlite3_prepare_v2(this->storage->GetDataBase(), sql, -1, &statement, nullptr) == SQLITE_OK) {
                    this->mutex.lock();

                    char uuidString[37]= {0};
                    uuid_unparse(updateMessage->GetUuid(), uuidString);
                    int i = 1;
                    sqlite3_bind_text(statement, i++, uuidString, -1, nullptr);
                    sqlite3_bind_text(statement, i++, updateMessage->GetApplicationName().c_str(), -1, nullptr);
                    sqlite3_bind_text(statement, i++, updateMessage->GetKey().c_str(), -1, nullptr);
                    sqlite3_bind_text(statement, i++, updateMessage->GetType().c_str(), -1, nullptr);
                    sqlite3_bind_text(statement, i++, updateMessage->GetValue().c_str(), -1, nullptr);
                    sqlite3_bind_int64(statement, i++, updateMessage->GetLastUpdate());
                    sqlite3_bind_int(statement, i, updateMessage->GetLastUpdateServerId());

                    int step = sqlite3_step(statement);
                    sqlite3_finalize(statement);

                    this->mutex.unlock();
                    return (step == SQLITE_DONE);
                }

                return false;
            }

            bool MessageService::NewDeleteMessage(Entity::DeleteMessage *deleteMessage) {
                if (this->Exist(deleteMessage->GetUuid())) {
                    return false;
                }

                const char *sql = "INSERT INTO [message] "
                                  "([uuid], [item_application_name], [item_key], "
                                  "[message_type], [last_update], [last_update_id]) "
                                  "VALUES (?,?,?,?,?,?);";
                sqlite3_stmt *statement = nullptr;
                if (sqlite3_prepare_v2(this->storage->GetDataBase(), sql, -1, &statement, nullptr) == SQLITE_OK) {
                    this->mutex.lock();

                    char uuidString[37]= {0};
                    uuid_unparse(deleteMessage->GetUuid(), uuidString);
                    int i = 1;
                    sqlite3_bind_text(statement, i++, uuidString, -1, nullptr);
                    sqlite3_bind_text(statement, i++, deleteMessage->GetApplicationName().c_str(), -1, nullptr);
                    sqlite3_bind_text(statement, i++, deleteMessage->GetKey().c_str(), -1, nullptr);
                    sqlite3_bind_text(statement, i++, deleteMessage->GetType().c_str(), -1, nullptr);
                    sqlite3_bind_int64(statement, i++, deleteMessage->GetLastUpdate());
                    sqlite3_bind_int(statement, i, deleteMessage->GetLastUpdateServerId());

                    int step = sqlite3_step(statement);
                    sqlite3_finalize(statement);

                    this->mutex.unlock();
                    return (step == SQLITE_DONE);
                }

                return false;
            }

            bool
            MessageService::NewIncrementalUpdateMessage(Entity::IncrementalUpdateMessage *incrementalUpdateMessage) {
                if (this->Exist(incrementalUpdateMessage->GetUuid())) {
                    return false;
                }

                const char *sql = "INSERT INTO [message] "
                                  "([uuid], [item_application_name], [item_key], [message_type]"
                                  ", [base_message_uuid], [atomic_operation], [new_value]"
                                  ", [last_update], [last_update_id]) "
                                  "VALUES (?,?,?,?,?, ?, ?, ?,?);";
                sqlite3_stmt *statement = nullptr;
                if (sqlite3_prepare_v2(this->storage->GetDataBase(), sql, -1, &statement, nullptr) == SQLITE_OK) {
                    this->mutex.lock();

                    char uuidString[37] = {0};
                    char baseMessageUuidString[37] = {0};
                    uuid_unparse(incrementalUpdateMessage->GetUuid(), uuidString);
                    uuid_unparse(incrementalUpdateMessage->GetBaseMessageUuid(), baseMessageUuidString);

                    int i = 1;
                    sqlite3_bind_text(statement, i++, uuidString, -1, nullptr);
                    sqlite3_bind_text(statement, i++, incrementalUpdateMessage->GetApplicationName().c_str(), -1, nullptr);
                    sqlite3_bind_text(statement, i++, incrementalUpdateMessage->GetKey().c_str(), -1, nullptr);
                    sqlite3_bind_text(statement, i++, incrementalUpdateMessage->GetType().c_str(), -1, nullptr);
                    sqlite3_bind_text(statement, i++, baseMessageUuidString, -1, nullptr);
                    sqlite3_bind_text(statement, i++, incrementalUpdateMessage->GetAtomicOperation().c_str(), -1, nullptr);
                    sqlite3_bind_text(statement, i++, incrementalUpdateMessage->GetValue().c_str(), -1, nullptr);
                    sqlite3_bind_int64(statement, i++, incrementalUpdateMessage->GetLastUpdate());
                    sqlite3_bind_int(statement, i, incrementalUpdateMessage->GetLastUpdateServerId());

                    int step = sqlite3_step(statement);
                    sqlite3_finalize(statement);

                    this->mutex.unlock();
                    return (step == SQLITE_DONE);
                }

                return false;
            }

            std::shared_ptr<Entity::AbstractMessage> MessageService::GetMessageByUuid(uuid_t messageUuid) {
                // TODO: Implement this
                return std::shared_ptr<Entity::AbstractMessage>();
            }

            std::vector<std::shared_ptr<Entity::AbstractMessage>>
            MessageService::FindMessages(const std::string &applicationName, const std::string &key) {
                // TODO: Implement this
                return std::vector<std::shared_ptr<Entity::AbstractMessage>>();
            }

            std::shared_ptr<Entity::AbstractMessage> MessageService::ParseMessage(sqlite3_stmt *statement) {
                // TODO: Implement this
                return std::shared_ptr<Entity::AbstractMessage>();
            }
        }
    }
}