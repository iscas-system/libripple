// Copyright (c) 2023 Institute of Software, Chinese Academy of Sciences
// libripple is licensed under Mulan PSL v2.
// You can use this software according to the terms and conditions of the Mulan PSL v2.
// You may obtain a copy of Mulan PSL v2 at:
//          http://license.coscl.org.cn/MulanPSL2
// THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
// EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
// MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
// See the Mulan PSL v2 for more details.

#ifndef LIBRIPPLE_OVERLAY_H
#define LIBRIPPLE_OVERLAY_H

#include <vector>
#include <memory>
#include "NodeMetadata.h"
#include "AbstractMessage.h"

namespace Ripple {
    namespace Server {
        namespace Core {
            namespace Overlay {

                class Overlay {
                public:
                    Overlay();

                    virtual ~Overlay();

                    Overlay(const Overlay &) = delete;

                    Overlay &operator=(const Overlay &) = delete;

                    virtual void
                    BuildOverlay(std::vector<std::shared_ptr<Ripple::Common::Entity::NodeMetadata>> nodeList) = 0;

                    virtual std::vector<std::shared_ptr<Ripple::Common::Entity::NodeMetadata>>
                    CalculateNodesToSync(std::shared_ptr<Ripple::Common::Entity::AbstractMessage> message,
                                         std::shared_ptr<Ripple::Common::Entity::NodeMetadata> source,
                                         std::shared_ptr<Ripple::Common::Entity::NodeMetadata> current) = 0;

                    virtual std::vector<std::shared_ptr<Ripple::Common::Entity::NodeMetadata>>
                    CalculateNodesToCollectAck(std::shared_ptr<Ripple::Common::Entity::AbstractMessage> message) = 0;
                };
            }
        }
    }
} // Ripple

#endif //LIBRIPPLE_OVERLAY_H
