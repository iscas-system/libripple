// Copyright (c) 2023 Institute of Software, Chinese Academy of Sciences
// libripple is licensed under Mulan PSL v2.
// You can use this software according to the terms and conditions of the Mulan PSL v2.
// You may obtain a copy of Mulan PSL v2 at:
//          http://license.coscl.org.cn/MulanPSL2
// THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
// EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
// MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
// See the Mulan PSL v2 for more details.

#include <queue>
#include "CompleteTree.h"

namespace Ripple {
    CompleteTree::CompleteTree(int branch, std::vector<std::shared_ptr<NodeMetadata>> nodeList)
            : branch(branch),
              nodeList(std::vector<std::shared_ptr<TreeNode>>()) {
        this->buildCompleteTree(nodeList);
    }

    CompleteTree::~CompleteTree() {

    }

    const int CompleteTree::GetBranch() const {
        return this->branch;
    }

    void CompleteTree::SetBranch(int branch) {
        this->branch = branch;
    }

    const std::shared_ptr<TreeNode> &CompleteTree::GetRoot() const {
        return this->root;
    }

    void CompleteTree::SetRoot(std::shared_ptr<TreeNode> root) {
        this->root = std::move(root);
    }

    const std::vector<std::shared_ptr<TreeNode>> &CompleteTree::GetNodeList() const {
        return this->nodeList;
    }

    void CompleteTree::SetNodeList(std::vector<std::shared_ptr<TreeNode>> nodeList) {
        this->nodeList = std::move(nodeList);
    }

    void CompleteTree::buildCompleteTree(std::vector<std::shared_ptr<NodeMetadata>> nodeList) {
        for (auto it = nodeList.begin(); it != nodeList.end(); it++) {
            this->nodeList.push_back(std::make_shared<TreeNode>(*it));
        }

        std::queue<std::shared_ptr<TreeNode>> nodes;
        std::queue<std::shared_ptr<TreeNode>> toAssign;
        for (auto it = this->GetNodeList().begin(); it != this->GetNodeList().end(); it++) {
            nodes.push(*it);
            toAssign.push(*it);
        }

        this->SetRoot(toAssign.front());
        toAssign.pop();
        for (auto it = this->GetNodeList().begin(); it != this->GetNodeList().end(); it++) {
            if (!nodes.empty()) {
                auto treeNode = nodes.front();
                nodes.pop();
                int i = 0;
                for (i = 0; i < this->GetBranch(); i++) {
                    if (!toAssign.empty()) {
                        auto element = toAssign.front();
                        toAssign.pop();
                        treeNode->GetChildren().push_back(element);
                    }
                }
            }
        }
    }

} // Ripple