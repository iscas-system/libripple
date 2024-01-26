// Copyright (c) 2023 Institute of Software, Chinese Academy of Sciences
// libripple is licensed under Mulan PSL v2.
// You can use this software according to the terms and conditions of the Mulan PSL v2.
// You may obtain a copy of Mulan PSL v2 at:
//          http://license.coscl.org.cn/MulanPSL2
// THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
// EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
// MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
// See the Mulan PSL v2 for more details.

#include "DeleteMessage.h"

#include <utility>
#include "Constants.h"

namespace Ripple {
    namespace Common {
        namespace Entity {
            DeleteMessage::DeleteMessage() {

            }

            DeleteMessage::DeleteMessage(uuid_t uuid, std::string applicationName, std::string key, time_t lastUpdate,
                                         int lastUpdateServerId) : AbstractMessage(uuid, MESSAGE_TYPE_DELETE,
                                                                                   std::move(applicationName),
                                                                                   std::move(key), lastUpdate,
                                                                                   lastUpdateServerId) {

            }

            DeleteMessage::DeleteMessage(std::string applicationName, std::string key, time_t lastUpdate,
                                         int lastUpdateServerId) : DeleteMessage(nullptr,
                                                                                 std::move(applicationName),
                                                                                 std::move(key), lastUpdate,
                                                                                 lastUpdateServerId) {
                uuid_t uuid;
                uuid_generate(uuid);
                this->SetUuid(uuid);
            }

            DeleteMessage::~DeleteMessage() {

            }
        }
    }
}