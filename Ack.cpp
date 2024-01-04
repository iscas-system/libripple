// Copyright (c) 2023 Institute of Software, Chinese Academy of Sciences
// libripple is licensed under Mulan PSL v2.
// You can use this software according to the terms and conditions of the Mulan PSL v2.
// You may obtain a copy of Mulan PSL v2 at:
//          http://license.coscl.org.cn/MulanPSL2
// THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
// EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
// MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
// See the Mulan PSL v2 for more details.

#include "Ack.h"

namespace Ripple {
    namespace Common {
        namespace Entity {
            Ack::Ack() {
                uuid_clear(this->messageUuid);
                this->SetNodeList(std::set<int>());
                this->SetAckNodes(std::set<int>());
            }

            Ack::~Ack() {

            }

            const uuid_t &Ack::GetMessageUuid() const {
                return this->messageUuid;
            }

            void Ack::SetMessageUuid(uuid_t messageUuid) {
                if (messageUuid != nullptr) {
                    uuid_copy(this->messageUuid, messageUuid);
                }
            }

            const std::set<int> &Ack::GetNodeList() const {
                return this->nodeList;
            }

            void Ack::SetNodeList(std::set<int> nodeList) {
                this->nodeList = std::move(nodeList);
            }

            const std::set<int> &Ack::GetAckNodes() const {
                return this->ackNodes;
            }

            void Ack::SetAckNodes(std::set<int> ackNodes) {
                this->ackNodes = std::move(ackNodes);
            }
        }
    }
}