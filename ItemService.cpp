// Copyright (c) 2023 Institute of Software, Chinese Academy of Sciences
// libripple is licensed under Mulan PSL v2.
// You can use this software according to the terms and conditions of the Mulan PSL v2.
// You may obtain a copy of Mulan PSL v2 at:
//          http://license.coscl.org.cn/MulanPSL2
// THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
// EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
// MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
// See the Mulan PSL v2 for more details.

#include "ItemService.h"
#include <memory>
#include <iostream>

// TODO: Implement this
namespace Ripple {
    namespace Common {
        namespace Storage {
            ItemService::ItemService(Storage *storage) {
                this->storage = storage;
            }

            ItemService::~ItemService() {

            }

            std::shared_ptr<Entity::Item> ItemService::GetItem(std::string applicationName, std::string key) {
                std::shared_ptr<Entity::Item> ret = nullptr;
                const char *sql = "SELECT * FROM [item] WHERE [application_name] = ? AND [key] = ?;";
                sqlite3_stmt *statement = nullptr;
                if (sqlite3_prepare_v2(this->storage->GetDataBase(), sql, -1, &statement, nullptr) == SQLITE_OK) {
                    sqlite3_bind_text(statement, 1, applicationName.c_str(), -1, nullptr);
                    sqlite3_bind_text(statement, 2, key.c_str(), -1, nullptr);
                }
                int step = sqlite3_step(statement);
                if (step == SQLITE_ROW) {
                    // 0: application_name, 1: key
                    std::string retApplicationName = std::string((const char *) sqlite3_column_text(statement, 0));
                    std::string retKey = std::string((const char *) sqlite3_column_text(statement, 1));
                    ret = std::make_shared<Entity::Item>(retApplicationName, retKey);
                }
                sqlite3_finalize(statement);
                return ret;
            }
        }
    }
}