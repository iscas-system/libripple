// Copyright (c) 2023 Institute of Software, Chinese Academy of Sciences
// libripple is licensed under Mulan PSL v2.
// You can use this software according to the terms and conditions of the Mulan PSL v2.
// You may obtain a copy of Mulan PSL v2 at:
//          http://license.coscl.org.cn/MulanPSL2
// THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
// EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
// MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
// See the Mulan PSL v2 for more details.

#ifndef LIBRIPPLE_COMPLETETREE_H
#define LIBRIPPLE_COMPLETETREE_H

#include <memory>
#include <vector>
#include "TreeNode.h"

namespace Ripple {

    class CompleteTree {
    public:
        CompleteTree(int branch, std::vector<std::shared_ptr<NodeMetadata>> nodeList);

        virtual ~CompleteTree();

        CompleteTree(const CompleteTree &) = delete;

        CompleteTree &operator=(const CompleteTree &) = delete;

        const int GetBranch() const;

        void SetBranch(int branch);

        const std::shared_ptr<TreeNode> & GetRoot() const;

        void SetRoot(std::shared_ptr<TreeNode> root);

        const std::vector<std::shared_ptr<TreeNode>> &GetNodeList() const;

        void SetNodeList(std::vector<std::shared_ptr<TreeNode>> nodeList);

    private:
        int branch;
        std::shared_ptr<TreeNode> root;
        std::vector<std::shared_ptr<TreeNode>> nodeList;
        void buildCompleteTree(std::vector<std::shared_ptr<NodeMetadata>> nodeList);
    };

} // Ripple

#endif //LIBRIPPLE_COMPLETETREE_H
