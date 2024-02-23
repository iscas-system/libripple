// Copyright (c) 2023 Institute of Software, Chinese Academy of Sciences
// libripple is licensed under Mulan PSL v2.
// You can use this software according to the terms and conditions of the Mulan PSL v2.
// You may obtain a copy of Mulan PSL v2 at:
//          http://license.coscl.org.cn/MulanPSL2
// THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
// EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
// MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
// See the Mulan PSL v2 for more details.

#include <memory>
#include <sstream>
#include <iterator>
#include "AckService.h"

// TODO: Implement this
namespace Ripple {
    namespace Common {
        namespace Storage {
            AckService::AckService(Storage *storage) {
                this->storage = storage;
            }

            AckService::~AckService() {

            }

            bool AckService::InitializeAck(uuid_t uuid, std::set<int> nodeList) {
                const char *sql = "INSERT INTO [ack] ([message_uuid], [node_list], [ack_nodes]) VALUES (?,?,?);";
                sqlite3_stmt *statement = nullptr;
                if (sqlite3_prepare_v2(this->storage->GetDataBase(), sql, -1, &statement, nullptr) == SQLITE_OK) {
                    this->mutex.lock();

                    std::stringstream ss;
                    std::copy(nodeList.begin(), nodeList.end(), std::ostream_iterator<int>(ss, " "));

                    char uuidString[37] = {0};
                    uuid_unparse(uuid, uuidString);
                    int i = 1;

                    // Ack: message_uuid, node_list, ack_nodes
                    sqlite3_bind_text(statement, i++, uuidString, -1, nullptr);
                    sqlite3_bind_text(statement, i++, ss.str().c_str(), -1, nullptr);
                    sqlite3_bind_text(statement, i, "", -1, nullptr);

                    int step = sqlite3_step(statement);
                    sqlite3_finalize(statement);

                    this->mutex.unlock();
                    return (step == SQLITE_DONE);
                }

                return false;
            }

            std::shared_ptr<Entity::Ack> AckService::GetAck(uuid_t messageUuid) {
                std::shared_ptr<Entity::Ack> ret = nullptr;
                const char *sql = "SELECT * FROM [ack] WHERE [message_uuid] = ?;";
                sqlite3_stmt *statement = nullptr;
                if (sqlite3_prepare_v2(this->storage->GetDataBase(), sql, -1, &statement, nullptr) == SQLITE_OK) {
                    char uuidString[37] = {0};
                    uuid_unparse(messageUuid, uuidString);
                    sqlite3_bind_text(statement, 1, uuidString, -1, nullptr);

                    int step = sqlite3_step(statement);
                    if (step == SQLITE_ROW) {
                        ret = this->ParseAck(statement);

                    }
                    sqlite3_finalize(statement);
                }
                return ret;
            }

            std::shared_ptr<Entity::Ack> AckService::ParseAck(sqlite3_stmt *statement) const {
                // Ack: message_uuid, node_list, ack_nodes
                std::string retMessageUuid = std::string((const char *) sqlite3_column_text(statement, 0));
                std::string retNodeList = std::string((const char *) sqlite3_column_text(statement, 1));
                std::string retAckNodes = std::string((const char *) sqlite3_column_text(statement, 2));

                auto ret = std::make_shared<Entity::Ack>();
                uuid_parse(retMessageUuid.c_str(), ret->GetMessageUuid());
                std::stringstream nodeListStream(retNodeList);
                std::stringstream ackNodesStream(retAckNodes);
                int elem;
                while (nodeListStream >> elem) {
                    ret->GetNodeList().insert(elem);
                }
                while (ackNodesStream >> elem) {
                    ret->GetAckNodes().insert(elem);
                }

                return ret;
            }

            std::vector<std::shared_ptr<Entity::Ack>> AckService::GetAllAcks() {
                auto ret = std::vector<std::shared_ptr<Entity::Ack>>();
                const char *sql = "SELECT * FROM [ack];";
                sqlite3_stmt *statement = nullptr;
                if (sqlite3_prepare_v2(this->storage->GetDataBase(), sql, -1, &statement, nullptr) == SQLITE_OK) {
                    while (sqlite3_step(statement) == SQLITE_ROW) {
                        // 0: application_name, 1: key
                        ret.push_back(this->ParseAck(statement));
                    }
                    sqlite3_finalize(statement);
                }
                return ret;
            }

            bool AckService::RecordAck(uuid_t messageUuid, int nodeId) {
                auto ack = this->GetAck(messageUuid);
                if (ack->GetAckNodes().find(nodeId) == ack->GetAckNodes().end()) {
                    ack->GetAckNodes().insert(nodeId);
                }

                const char *sql = "UPDATE [ack] SET [ack_nodes] = ? WHERE [message_uuid] = ?;";
                sqlite3_stmt *statement = nullptr;
                if (sqlite3_prepare_v2(this->storage->GetDataBase(), sql, -1, &statement, nullptr) == SQLITE_OK) {
                    this->mutex.lock();

                    std::stringstream ss;
                    std::copy(ack->GetAckNodes().begin(), ack->GetAckNodes().end(),
                              std::ostream_iterator<int>(ss, " "));

                    char uuidString[37] = {0};
                    uuid_unparse(ack->GetMessageUuid(), uuidString);
                    int i = 1;

                    sqlite3_bind_text(statement, i++, ss.str().c_str(), -1, nullptr);
                    sqlite3_bind_text(statement, i++, uuidString, -1, nullptr);

                    int step = sqlite3_step(statement);
                    sqlite3_finalize(statement);

                    this->mutex.unlock();
                    return (step == SQLITE_DONE);
                }

                return false;
            }


        }
    }
}