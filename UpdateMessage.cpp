// Copyright (c) 2023 Institute of Software, Chinese Academy of Sciences
// libripple is licensed under Mulan PSL v2.
// You can use this software according to the terms and conditions of the Mulan PSL v2.
// You may obtain a copy of Mulan PSL v2 at:
//          http://license.coscl.org.cn/MulanPSL2
// THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
// EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
// MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
// See the Mulan PSL v2 for more details.


#include "UpdateMessage.h"

#include <utility>
#include "Constants.h"

namespace Ripple {
    namespace Common {
        namespace Entity {
            const std::string &UpdateMessage::GetValue() const {
                return this->value;
            }

            void UpdateMessage::SetValue(std::string value) {
                this->value = std::move(value);
            }

            UpdateMessage::UpdateMessage(uuid_t uuid, std::string applicationName, std::string key, std::string value,
                                         time_t lastUpdate, int lastUpdateServerId) : AbstractMessage(uuid,
                                                                                                      MESSAGE_TYPE_UPDATE,
                                                                                                      std::move(
                                                                                                              applicationName),
                                                                                                      std::move(key),
                                                                                                      lastUpdate,
                                                                                                      lastUpdateServerId) {
                this->SetValue(std::move(value));
            }

            UpdateMessage::UpdateMessage(std::string applicationName, std::string key, std::string value,
                                         time_t lastUpdate, int lastUpdateServerId) : UpdateMessage(nullptr,
                                                                                                    std::move(
                                                                                                            applicationName),
                                                                                                    std::move(key),
                                                                                                    std::move(value),
                                                                                                    lastUpdate,
                                                                                                    lastUpdateServerId) {
                uuid_t uuid;
                uuid_generate(uuid);
                this->SetUuid(uuid);
            }

            UpdateMessage::UpdateMessage() {

            }

            UpdateMessage::~UpdateMessage() {

            }
        }
    }
}