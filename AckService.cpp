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

            bool AckService::InitializeAck(unsigned char *uuid, std::vector<int> nodeList) {
                // TODO: Implement this
                return false;
            }

            std::shared_ptr<Entity::Ack> AckService::GetAck(uuid_t messageUuid) {
                // TODO: Implement this
                return nullptr;
            }

            std::vector<std::shared_ptr<Entity::Ack>> AckService::GetAllAcks() {
                // TODO: Implement this
                return std::vector<std::shared_ptr<Entity::Ack>>();
            }

            bool AckService::recordAck(unsigned char *messageUuid, int nodeId) {
                // TODO: Implement this
                return false;
            }


        }
    }
}