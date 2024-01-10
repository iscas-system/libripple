// Copyright (c) 2023 Institute of Software, Chinese Academy of Sciences
// libripple is licensed under Mulan PSL v2.
// You can use this software according to the terms and conditions of the Mulan PSL v2.
// You may obtain a copy of Mulan PSL v2 at:
//          http://license.coscl.org.cn/MulanPSL2
// THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
// EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
// MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
// See the Mulan PSL v2 for more details.

#include "Item.h"

namespace Ripple {
    namespace Common {
        namespace Entity {
            Item::Item() {

            }

            Item::Item(std::string applicationName, std::string key) {
                this->SetApplicationName(applicationName);
                this->SetKey(key);
            }

            Item::~Item() {

            }

            const std::string &Item::GetApplicationName() const {
                return this->applicationName;
            }

            void Item::SetApplicationName(std::string applicationName) {
                this->applicationName = std::move(applicationName);
            }

            const std::string &Item::GetKey() const {
                return this->key;
            }

            void Item::SetKey(std::string key) {
                this->key = std::move(key);
            }

            bool Item::operator==(const Item &item) {
                return (this->applicationName == item.applicationName
                        && this->key == item.key);
            }

        }
    }
}