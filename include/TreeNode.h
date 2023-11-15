// Copyright (c) 2023 Institute of Software, Chinese Academy of Sciences
// libripple is licensed under Mulan PSL v2.
// You can use this software according to the terms and conditions of the Mulan PSL v2.
// You may obtain a copy of Mulan PSL v2 at:
//          http://license.coscl.org.cn/MulanPSL2
// THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
// EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
// MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
// See the Mulan PSL v2 for more details.

#ifndef LIBRIPPLE_TREENODE_H
#define LIBRIPPLE_TREENODE_H

#include <memory>
#include <vector>
#include "NodeMetadata.h"

namespace Ripple {

    class TreeNode {
    public:
        TreeNode(std::shared_ptr<NodeMetadata> nodeMetadata);

        virtual ~TreeNode();

        TreeNode(const TreeNode &) = delete;

        TreeNode &operator=(const TreeNode &) = delete;

        const std::shared_ptr<NodeMetadata> &GetNodeMetadata() const;

        void SetNodeMetadata(std::shared_ptr<NodeMetadata> nodeMetadata);

        std::vector<std::shared_ptr<TreeNode>> &GetChildren();

        void SetChildren(std::vector<std::shared_ptr<TreeNode>> children);

    private:
        std::shared_ptr<NodeMetadata> nodeMetadata;
        std::vector<std::shared_ptr<TreeNode>> children;
    };

} // Ripple

#endif //LIBRIPPLE_TREENODE_H
