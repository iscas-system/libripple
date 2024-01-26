// Copyright (c) 2023 Institute of Software, Chinese Academy of Sciences
// libripple is licensed under Mulan PSL v2.
// You can use this software according to the terms and conditions of the Mulan PSL v2.
// You may obtain a copy of Mulan PSL v2 at:
//          http://license.coscl.org.cn/MulanPSL2
// THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
// EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
// MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
// See the Mulan PSL v2 for more details.

#include "IncrementalUpdateMessage.h"
#include "Constants.h"

#include <utility>

namespace Ripple {
    namespace Common {
        namespace Entity {
            uuid_t &IncrementalUpdateMessage::GetBaseMessageUuid() {
                return this->baseMessageUuid;
            }

            void IncrementalUpdateMessage::SetBaseMessageUuid(uuid_t baseMessageUuid) {
                if (baseMessageUuid != nullptr) {
                    uuid_copy(this->baseMessageUuid, baseMessageUuid);
                }
            }

            const std::string &IncrementalUpdateMessage::GetAtomicOperation() const {
                return this->atomicOperation;
            }

            void IncrementalUpdateMessage::SetAtomicOperation(std::string atomicOperation) {
                this->atomicOperation = std::move(atomicOperation);
            }

            const std::string &IncrementalUpdateMessage::GetValue() const {
                return this->value;
            }

            void IncrementalUpdateMessage::SetValue(std::string value) {
                this->value = std::move(value);
            }

            IncrementalUpdateMessage::IncrementalUpdateMessage() {

            }

            IncrementalUpdateMessage::~IncrementalUpdateMessage() {

            }

            IncrementalUpdateMessage::IncrementalUpdateMessage(uuid_t uuid, std::string applicationName,
                                                               std::string key,
                                                               uuid_t baseMessageUuid, std::string atomOperation,
                                                               std::string value,
                                                               time_t lastUpdate, int lastUpdateServerId)
                    : AbstractMessage(uuid,
                                      MESSAGE_TYPE_INCREMENTAL_UPDATE,
                                      std::move(
                                              applicationName),
                                      std::move(key),
                                      lastUpdate,
                                      lastUpdateServerId) {
                this->SetBaseMessageUuid(baseMessageUuid);
                this->SetAtomicOperation(std::move(atomOperation));
                this->SetValue(std::move(value));
            }

            IncrementalUpdateMessage::IncrementalUpdateMessage(std::string applicationName, std::string key,
                                                               uuid_t baseMessageUuid, std::string atomOperation,
                                                               std::string value,
                                                               time_t lastUpdate, int lastUpdateServerId)
                    : IncrementalUpdateMessage(nullptr,
                                               std::move(
                                                       applicationName),
                                               std::move(key), baseMessageUuid, std::move(atomOperation),
                                               std::move(value),
                                               lastUpdate,
                                               lastUpdateServerId) {
                uuid_t uuid;
                uuid_generate(uuid);
                this->SetUuid(uuid);
            }


        }
    }
}