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
#include "Constants.h"
#include <uuid/uuid.h>
#include <memory>

namespace Ripple {
    namespace Common {
        namespace Storage {
            MessageService::MessageService(Storage *storage) {
                this->storage = storage;
            }

            MessageService::~MessageService() {

            }

            bool MessageService::NewMessage(const std::shared_ptr<Entity::AbstractMessage> &message) {
                if (auto updateMessage = std::dynamic_pointer_cast<Entity::UpdateMessage>(message)) {
                    return this->NewUpdateMessage(updateMessage);
                } else if (auto deleteMessage = std::dynamic_pointer_cast<Entity::DeleteMessage>(message)) {
                    return this->NewDeleteMessage(deleteMessage);
                } else if (auto incrementalUpdateMessage = std::dynamic_pointer_cast<Entity::IncrementalUpdateMessage>(
                        message)) {
                    return this->NewIncrementalUpdateMessage(incrementalUpdateMessage);
                }
                return false;
            }

            bool MessageService::Exist(const uuid_t messageUuid) {
                bool ret = false;
                const char *sql = "SELECT * FROM [message] WHERE [uuid] = ?;";
                sqlite3_stmt *statement = nullptr;
                if (sqlite3_prepare_v2(this->storage->GetDataBase(), sql, -1, &statement, nullptr) == SQLITE_OK) {
                    char uuidString[37] = {0};
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

            bool MessageService::NewUpdateMessage(const std::shared_ptr<Entity::UpdateMessage> &updateMessage) {
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

                    char uuidString[37] = {0};
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

            bool MessageService::NewDeleteMessage(const std::shared_ptr<Entity::DeleteMessage> &deleteMessage) {
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

                    char uuidString[37] = {0};
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
            MessageService::NewIncrementalUpdateMessage(
                    const std::shared_ptr<Entity::IncrementalUpdateMessage> &incrementalUpdateMessage) {
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
                    sqlite3_bind_text(statement, i++, incrementalUpdateMessage->GetApplicationName().c_str(), -1,
                                      nullptr);
                    sqlite3_bind_text(statement, i++, incrementalUpdateMessage->GetKey().c_str(), -1, nullptr);
                    sqlite3_bind_text(statement, i++, incrementalUpdateMessage->GetType().c_str(), -1, nullptr);
                    sqlite3_bind_text(statement, i++, baseMessageUuidString, -1, nullptr);
                    sqlite3_bind_text(statement, i++, incrementalUpdateMessage->GetAtomicOperation().c_str(), -1,
                                      nullptr);
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
                std::shared_ptr<Entity::AbstractMessage> message = nullptr;
                const char *sql = "SELECT * FROM [message] WHERE [uuid] = ?;";
                sqlite3_stmt *statement = nullptr;
                if (sqlite3_prepare_v2(this->storage->GetDataBase(), sql, -1, &statement, nullptr) == SQLITE_OK) {
                    char uuidString[37] = {0};
                    uuid_unparse(messageUuid, uuidString);
                    sqlite3_bind_text(statement, 1, uuidString, -1, nullptr);

                    int step = sqlite3_step(statement);
                    if (step == SQLITE_ROW) {
                        message = this->ParseMessage(statement);
                    }
                    sqlite3_finalize(statement);
                }
                return message;
            }

            std::vector<std::shared_ptr<Entity::AbstractMessage>>
            MessageService::FindMessages(const std::string &applicationName, const std::string &key) {
                auto ret = std::vector<std::shared_ptr<Entity::AbstractMessage>>();
                const char *sql = "SELECT * FROM [message] WHERE [item_application_name] = ? AND [item_key] = ?;";
                sqlite3_stmt *statement = nullptr;
                if (sqlite3_prepare_v2(this->storage->GetDataBase(), sql, -1, &statement, nullptr) == SQLITE_OK) {
                    sqlite3_bind_text(statement, 1, applicationName.c_str(), -1, nullptr);
                    sqlite3_bind_text(statement, 2, key.c_str(), -1, nullptr);

                    while (sqlite3_step(statement) == SQLITE_ROW) {
                        ret.push_back(this->ParseMessage(statement));
                    }
                    sqlite3_finalize(statement);
                }
                return ret;
            }

            std::shared_ptr<Entity::AbstractMessage> MessageService::ParseMessage(sqlite3_stmt *statement) {
                std::shared_ptr<Entity::AbstractMessage> message = nullptr;
                // Message: 0:uuid, 1:item_application_name, 2:item_key, 3:message_type
                //          4:base_message_uuid, 5:atomic_operation, 6:new_value, 7:last_update, 8:last_update_id

                std::string messageType = std::string((const char *) sqlite3_column_text(statement, 3));
                if (messageType == MESSAGE_TYPE_UPDATE) {
                    auto updateMessage = std::make_shared<Entity::UpdateMessage>();
                    message = updateMessage;
                    this->DoParseAbstractMessage(statement, message, messageType);
                    updateMessage->SetValue(std::string((const char *) sqlite3_column_text(statement, 6)));
                } else if (messageType == MESSAGE_TYPE_DELETE) {
                    auto deleteMessage = std::make_shared<Entity::DeleteMessage>();
                    message = deleteMessage;
                    this->DoParseAbstractMessage(statement, message, messageType);
                } else if (messageType == MESSAGE_TYPE_INCREMENTAL_UPDATE) {
                    auto incrementalUpdateMessage = std::make_shared<Entity::IncrementalUpdateMessage>();
                    message = incrementalUpdateMessage;
                    this->DoParseAbstractMessage(statement, message, messageType);

                    std::string baseMessageUuid = std::string((const char *) sqlite3_column_text(statement, 4));
                    uuid_parse(baseMessageUuid.c_str(), incrementalUpdateMessage->GetBaseMessageUuid());
                    incrementalUpdateMessage->SetAtomicOperation(
                            std::string((const char *) sqlite3_column_text(statement, 5)));
                    incrementalUpdateMessage->SetValue(std::string((const char *) sqlite3_column_text(statement, 6)));
                }
                return message;
            }

            void MessageService::DoParseAbstractMessage(sqlite3_stmt *statement,
                                                        std::shared_ptr<Entity::AbstractMessage> &message,
                                                        std::string &messageType) const {
                message->SetType(messageType);
                std::string uuid = std::string((const char *) sqlite3_column_text(statement, 0));
                uuid_parse(uuid.c_str(), message->GetUuid());
                message->SetApplicationName(std::string((const char *) sqlite3_column_text(statement, 1)));
                message->SetKey(std::string((const char *) sqlite3_column_text(statement, 2)));
                message->SetLastUpdate(sqlite3_column_int64(statement, 7));
                message->SetLastUpdateServerId(sqlite3_column_int(statement, 8));
            }
        }
    }
}