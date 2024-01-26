// Copyright (c) 2023 Institute of Software, Chinese Academy of Sciences
// libripple is licensed under Mulan PSL v2.
// You can use this software according to the terms and conditions of the Mulan PSL v2.
// You may obtain a copy of Mulan PSL v2 at:
//          http://license.coscl.org.cn/MulanPSL2
// THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
// EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
// MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
// See the Mulan PSL v2 for more details.

#include "AbstractMessage.h"

#include <utility>

namespace Ripple {
    namespace Common {
        namespace Entity {
            AbstractMessage::AbstractMessage() {
                uuid_clear(this->uuid);
                this->lastUpdate = 0;
                this->lastUpdateServerId = 0;
            }

            AbstractMessage::AbstractMessage(uuid_t uuid, std::string type, std::string applicationName,
                                             std::string key,
                                             time_t lastUpdate, int lastUpdateServerId) {
                this->SetUuid(uuid);
                this->SetType(std::move(type));
                this->SetApplicationName(std::move(applicationName));
                this->SetKey(std::move(key));
                this->SetLastUpdate(lastUpdate);
                this->SetLastUpdateServerId(lastUpdateServerId);
            }

            AbstractMessage::~AbstractMessage() {

            }

            uuid_t &AbstractMessage::GetUuid() {
                return this->uuid;
            }

            void AbstractMessage::SetUuid(uuid_t uuid) {
                if (uuid != nullptr) {
                    uuid_copy(this->uuid, uuid);
                }
            }

            const std::string &AbstractMessage::GetType() const {
                return this->type;
            }

            void AbstractMessage::SetType(std::string type) {
                this->type = std::move(type);
            }

            const std::string &AbstractMessage::GetApplicationName() const {
                return this->applicationName;
            }

            void AbstractMessage::SetApplicationName(std::string applicationName) {
                this->applicationName = std::move(applicationName);
            }

            const std::string &AbstractMessage::GetKey() const {
                return this->key;
            }

            void AbstractMessage::SetKey(std::string key) {
                this->key = std::move(key);
            }

            time_t AbstractMessage::GetLastUpdate() const {
                return this->lastUpdate;
            }

            void AbstractMessage::SetLastUpdate(time_t lastUpdate) {
                this->lastUpdate = lastUpdate;
            }

            int AbstractMessage::GetLastUpdateServerId() const {
                return this->lastUpdateServerId;
            }

            void AbstractMessage::SetLastUpdateServerId(int lastUpdateServerId) {
                this->lastUpdateServerId = lastUpdateServerId;
            }


        }
    }
} // Ripple