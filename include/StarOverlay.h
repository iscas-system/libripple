// Copyright (c) 2023 Institute of Software, Chinese Academy of Sciences
// libripple is licensed under Mulan PSL v2.
// You can use this software according to the terms and conditions of the Mulan PSL v2.
// You may obtain a copy of Mulan PSL v2 at:
//          http://license.coscl.org.cn/MulanPSL2
// THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
// EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
// MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
// See the Mulan PSL v2 for more details.

#ifndef LIBRIPPLE_STAROVERLAY_H
#define LIBRIPPLE_STAROVERLAY_H

#include "Overlay.h"

namespace Ripple {
    namespace Server {
        namespace Core {
            namespace Overlay {

                class StarOverlay final : public Overlay {
                public:
                    StarOverlay();

                    ~StarOverlay() final;

                    StarOverlay(const StarOverlay &) = delete;

                    StarOverlay &operator=(const StarOverlay &) = delete;

                    const std::vector<std::shared_ptr<Ripple::Common::Entity::NodeMetadata>> &GetNodeList() const;

                    void SetNodeList(std::vector<std::shared_ptr<Ripple::Common::Entity::NodeMetadata>> nodeList);

                    void
                    BuildOverlay(std::vector<std::shared_ptr<Ripple::Common::Entity::NodeMetadata>> nodeList) override;

                    std::vector<std::shared_ptr<Ripple::Common::Entity::NodeMetadata>>
                    CalculateNodesToSync(std::shared_ptr<Ripple::Common::Entity::AbstractMessage> message,
                                         std::shared_ptr<Ripple::Common::Entity::NodeMetadata> source,
                                         std::shared_ptr<Ripple::Common::Entity::NodeMetadata> current) override;

                    std::vector<std::shared_ptr<Ripple::Common::Entity::NodeMetadata>>
                    CalculateNodesToCollectAck(
                            std::shared_ptr<Ripple::Common::Entity::AbstractMessage> message) override;

                private:
                    std::vector<std::shared_ptr<Ripple::Common::Entity::NodeMetadata>> nodeList;
                };
            }
        }
    }
} // Ripple

#endif //LIBRIPPLE_STAROVERLAY_H
