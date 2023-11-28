// Copyright (c) 2023 Institute of Software, Chinese Academy of Sciences
// libripple is licensed under Mulan PSL v2.
// You can use this software according to the terms and conditions of the Mulan PSL v2.
// You may obtain a copy of Mulan PSL v2 at:
//          http://license.coscl.org.cn/MulanPSL2
// THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
// EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
// MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
// See the Mulan PSL v2 for more details.

#include "StarOverlay.h"
#include "Logger.h"

namespace Ripple {
    namespace Server {
        namespace Core {
            namespace Overlay {

                StarOverlay::StarOverlay() {

                }

                StarOverlay::~StarOverlay() {

                }

                const std::vector<std::shared_ptr<Ripple::Common::Entity::NodeMetadata>> &
                StarOverlay::GetNodeList() const {
                    return this->nodeList;
                }

                void
                StarOverlay::SetNodeList(std::vector<std::shared_ptr<Ripple::Common::Entity::NodeMetadata>> nodeList) {
                    this->nodeList = std::move(nodeList);
                }

                void
                StarOverlay::BuildOverlay(std::vector<std::shared_ptr<Ripple::Common::Entity::NodeMetadata>> nodeList) {
                    this->SetNodeList(nodeList);
                }

                std::vector<std::shared_ptr<Ripple::Common::Entity::NodeMetadata>>
                StarOverlay::CalculateNodesToSync(std::shared_ptr<Ripple::Common::Entity::AbstractMessage> message,
                                                  std::shared_ptr<Ripple::Common::Entity::NodeMetadata> source,
                                                  std::shared_ptr<Ripple::Common::Entity::NodeMetadata> current) {
                    Ripple::Common::Logger::Info("StarOverlay",
                                                 "CalculateNodesToSync() called. sourceId = %d, currentId = %d",
                                                 source->GetId(),
                                                 current->GetId());
                    if (source->GetId() != current->GetId()) {
                        // Leaf node
                        Ripple::Common::Logger::Info("StarOverlay", "Leaf node.");
                        return std::vector<std::shared_ptr<Ripple::Common::Entity::NodeMetadata>>();
                    } else {
                        std::vector<std::shared_ptr<Ripple::Common::Entity::NodeMetadata>> ret;
                        for (auto it = this->GetNodeList().begin(); it != this->GetNodeList().end(); it++) {
                            if ((*it)->GetId() != current->GetId()) {
                                ret.push_back(*it);
                                Ripple::Common::Logger::Info("StarOverlay", "Attempting to send to node %d (%s:%d).",
                                                             (*it)->GetId(),
                                                             (*it)->GetAddress().c_str(), (*it)->GetPort());
                            }
                        }
                        return ret;
                    }
                }

                std::vector<std::shared_ptr<Ripple::Common::Entity::NodeMetadata>>
                StarOverlay::CalculateNodesToCollectAck(
                        std::shared_ptr<Ripple::Common::Entity::AbstractMessage> message) {
                    return this->GetNodeList();
                }
            }
        }
    }
} // Ripple