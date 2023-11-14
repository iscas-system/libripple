// Copyright (c) 2023 Institute of Software, Chinese Academy of Sciences
// libripple is licensed under Mulan PSL v2.
// You can use this software according to the terms and conditions of the Mulan PSL v2.
// You may obtain a copy of Mulan PSL v2 at:
//          http://license.coscl.org.cn/MulanPSL2
// THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
// EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
// MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
// See the Mulan PSL v2 for more details.

#include "TreeOverlay.h"

namespace Ripple {
    TreeOverlay::TreeOverlay() {

    }

    TreeOverlay::~TreeOverlay() {

    }

    void TreeOverlay::BuildOverlay(std::vector<std::shared_ptr<NodeMetadata>> nodeList) {

    }

    std::vector<std::shared_ptr<NodeMetadata>>
    TreeOverlay::CalculateNodesToSync(std::shared_ptr<AbstractMessage> message, std::shared_ptr<NodeMetadata> source,
                                      std::shared_ptr<NodeMetadata> current) {
        return std::vector<std::shared_ptr<NodeMetadata>>();
    }

    std::vector<std::shared_ptr<NodeMetadata>>
    TreeOverlay::CalculateNodesToCollectAck(std::shared_ptr<AbstractMessage> message) {
        return std::vector<std::shared_ptr<NodeMetadata>>();
    }
} // Ripple