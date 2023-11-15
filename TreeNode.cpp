// Copyright (c) 2023 Institute of Software, Chinese Academy of Sciences
// libripple is licensed under Mulan PSL v2.
// You can use this software according to the terms and conditions of the Mulan PSL v2.
// You may obtain a copy of Mulan PSL v2 at:
//          http://license.coscl.org.cn/MulanPSL2
// THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
// EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
// MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
// See the Mulan PSL v2 for more details.

#include "TreeNode.h"

namespace Ripple {
    TreeNode::TreeNode(std::shared_ptr<NodeMetadata> nodeMetadata)
            : nodeMetadata(nodeMetadata),
              children(std::vector<std::shared_ptr<TreeNode>>()) {

    }

    TreeNode::~TreeNode() {

    }

    const std::shared_ptr<NodeMetadata> &TreeNode::GetNodeMetadata() const {
        return this->nodeMetadata;
    }

    void TreeNode::SetNodeMetadata(std::shared_ptr<NodeMetadata> nodeMetadata) {
        this->nodeMetadata = std::move(nodeMetadata);
    }

    std::vector<std::shared_ptr<TreeNode>> &TreeNode::GetChildren()  {
        return this->children;
    }

    void TreeNode::SetChildren(std::vector<std::shared_ptr<TreeNode>> children) {
        this->children = std::move(children);
    }
} // Ripple