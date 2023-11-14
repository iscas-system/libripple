// Copyright (c) 2023 Institute of Software, Chinese Academy of Sciences
// libripple is licensed under Mulan PSL v2.
// You can use this software according to the terms and conditions of the Mulan PSL v2.
// You may obtain a copy of Mulan PSL v2 at:
//          http://license.coscl.org.cn/MulanPSL2
// THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
// EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
// MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
// See the Mulan PSL v2 for more details.

#ifndef LIBRIPPLE_GOSSIPOVERLAY_H
#define LIBRIPPLE_GOSSIPOVERLAY_H

#include "Overlay.h"

namespace Ripple {

    class GossipOverlay final: public Overlay {
    public:
        GossipOverlay();

        virtual ~GossipOverlay() override;

        GossipOverlay(const GossipOverlay &) = delete;

        GossipOverlay &operator=(const GossipOverlay &) = delete;

        void BuildOverlay(std::vector<NodeMetadata *> nodeList) override;

        std::vector<NodeMetadata *>
        CalculateNodesToSync(AbstractMessage *message, NodeMetadata *source, NodeMetadata *current) override;

        std::vector<NodeMetadata *> CalculateNodesToCollectAck(AbstractMessage *message) override;
    };

} // Ripple

#endif //LIBRIPPLE_GOSSIPOVERLAY_H
