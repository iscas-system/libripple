// Copyright (c) 2023 Institute of Software, Chinese Academy of Sciences
// libripple is licensed under Mulan PSL v2.
// You can use this software according to the terms and conditions of the Mulan PSL v2.
// You may obtain a copy of Mulan PSL v2 at:
//          http://license.coscl.org.cn/MulanPSL2
// THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
// EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
// MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
// See the Mulan PSL v2 for more details.

#include <iostream>
#include "Storage.h"
#include "Logger.h"

// TODO: Implement this
namespace Ripple {
    namespace Common {
        namespace Storage {
            Storage::Storage(std::string fileName) {
                this->SetFileName(fileName);
                this->ackService.reset(new AckService(this));
                this->messageService.reset(new MessageService(this));
                this->itemService.reset(new ItemService(this));
                this->Initialize();
            }

            Storage::~Storage() {
                if (this->database != nullptr) {
                    sqlite3_close_v2(this->database);
                    this->database = nullptr;
                }
            }

            sqlite3 *Storage::GetDataBase() const {
                return this->database;
            }

            ItemService *Storage::GetItemService() const {
                return this->itemService.get();
            }

            const MessageService *Storage::GetMessageService() const {
                return this->messageService.get();
            }

            const AckService *Storage::GetAckService() const {
                return this->ackService.get();
            }

            const std::string &Storage::GetFileName() const {
                return this->fileName;
            }

            void Storage::SetFileName(std::string fileName) {
                this->fileName = std::move(fileName);
            }

            void Storage::Initialize() {
                int ret = sqlite3_open_v2(this->GetFileName().c_str(), &this->database,
                                          SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE, nullptr);
                if (ret) {
                    Logger::Error("Storage", "Can't open database: %s.", sqlite3_errmsg(this->database));
                } else {
                    this->InitializeTables();
                }
            }

            void Storage::DoExecuteStatement(const char *statement) {
                char *errmsg = nullptr;
                int ret = sqlite3_exec(this->database, statement, nullptr, nullptr, &errmsg);
                if (ret != SQLITE_OK) {
                    Logger::Error("Storage", "SQL error: %s.", errmsg);
                    sqlite3_free(errmsg);
                }
            }

            void Storage::InitializeTables() {
                this->DoExecuteStatement("PRAGMA foreign_keys = ON;");

                // Item: application_name, item_key
                this->DoExecuteStatement("CREATE TABLE IF NOT EXISTS [item] "
                                         "([application_name] TEXT NOT NULL,"
                                         " [key] TEXT NOT NULL, "
                                         "PRIMARY KEY ([application_name], [key]));");

                // Message: uuid, item_application_name, item_key, message_type, base_message_uuid, atomic_operation, new_value, last_update, last_update_id
                this->DoExecuteStatement("CREATE TABLE IF NOT EXISTS [message] "
                                         "([uuid] TEXT NOT NULL, "
                                         "[item_application_name] TEXT NOT NULL, "
                                         "[item_key] TEXT NOT NULL, "
                                         "[message_type] TEXT NOT NULL, "
                                         "[base_message_uuid] TEXT, "
                                         "[atomic_operation] TEXT, "
                                         "[new_value] TEXT, "
                                         "[last_update] INTEGER NOT NULL, "
                                         "[last_update_id] INTEGER NOT NULL, "
                                         "PRIMARY KEY ([uuid]), "
                                         "FOREIGN KEY ([item_application_name], [item_key]) "
                                         "REFERENCES [item]([application_name], [key]) "
                                         "ON DELETE CASCADE "
                                         "ON UPDATE CASCADE);");

                // Ack: message_uuid, node_list, ack_nodes
                this->DoExecuteStatement("CREATE TABLE IF NOT EXISTS [ack] "
                                         "([message_uuid] TEXT NOT NULL, "
                                         "[node_list] TEXT NOT NULL, "
                                         "[ack_nodes] TEXT, "
                                         "PRIMARY KEY ([message_uuid]), "
                                         "FOREIGN KEY ([message_uuid]) "
                                         "REFERENCES [message]([uuid]) "
                                         "ON DELETE CASCADE "
                                         "ON UPDATE CASCADE);");

            }
        }
    }
}