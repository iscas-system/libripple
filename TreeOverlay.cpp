// Copyright (c) 2023 Institute of Software, Chinese Academy of Sciences
// libripple is licensed under Mulan PSL v2.
// You can use this software according to the terms and conditions of the Mulan PSL v2.
// You may obtain a copy of Mulan PSL v2 at:
//          http://license.coscl.org.cn/MulanPSL2
// THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
// EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
// MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
// See the Mulan PSL v2 for more details.

#include <algorithm>
#include "TreeOverlay.h"
#include "Logger.h"

namespace Ripple {
    TreeOverlay::TreeOverlay(int branch)
            : trees(std::map<int, std::shared_ptr<CompleteTree>>()) {
        this->SetBranch(branch);
    }

    TreeOverlay::~TreeOverlay() {

    }

    void TreeOverlay::BuildOverlay(std::vector<std::shared_ptr<NodeMetadata>> nodeList) {
        this->SetNodeList(nodeList);
        for (auto it = nodeList.begin(); it != nodeList.end(); it++) {
            auto source = *it;
            std::vector<std::shared_ptr<NodeMetadata>> list = this->calculateNodeListForSource(source, nodeList);
            auto tree = std::make_shared<CompleteTree>(this->GetBranch(), list);
            this->GetTrees().insert(std::pair<int, std::shared_ptr<CompleteTree>>(source->GetId(), tree));
        }
    }

    std::vector<std::shared_ptr<NodeMetadata>>
    TreeOverlay::calculateNodeListForSource(std::shared_ptr<NodeMetadata> source,
                                            std::vector<std::shared_ptr<NodeMetadata>> nodeList) {
        std::vector<std::shared_ptr<NodeMetadata>> ret(nodeList);
        int i = 0;
        for (auto it = nodeList.begin(); it != nodeList.end(); it++) {
            if (source->GetId() == (*it)->GetId()) {
                break;
            }
            i++;
        }
        std::rotate(ret.begin(), ret.begin() + i, ret.end());
        return ret;
    }

    std::vector<std::shared_ptr<NodeMetadata>>
    TreeOverlay::generateNodeList(std::vector<std::shared_ptr<TreeNode>> treeNodeList) {
        std::vector<std::shared_ptr<NodeMetadata>> ret;
        for (auto it = treeNodeList.begin(); it != treeNodeList.end(); it++) {
            auto nodeMetadata = (*it)->GetNodeMetadata();
            Logger::Info("TreeOverlay", "Attempting to send to node %d (%s:%d).", nodeMetadata->GetId(),
                         nodeMetadata->GetAddress().c_str(), nodeMetadata->GetPort());
            ret.push_back(nodeMetadata);
        }
        return ret;
    }

    std::vector<std::shared_ptr<NodeMetadata>>
    TreeOverlay::CalculateNodesToSync(std::shared_ptr<AbstractMessage> message, std::shared_ptr<NodeMetadata> source,
                                      std::shared_ptr<NodeMetadata> current) {
        Logger::Info("TreeOverlay", "CalculateNodesToSync() called. sourceId = %d, currentId = %d.", source->GetId(),
                     current->GetId());
        auto iter = *(this->GetTrees().find(source->GetId()));
        auto treeNodeList = iter.second->GetNodeList();
        for (auto nodeIter = treeNodeList.begin(); nodeIter != treeNodeList.end(); nodeIter++) {
            if ((*nodeIter)->GetNodeMetadata()->GetId() == current->GetId()) {
                return this->generateNodeList((*nodeIter)->GetChildren());
            }
        }
        Logger::Info("TreeOverlay", "I cannot find children list for node %d.", current->GetId());
        return std::vector<std::shared_ptr<NodeMetadata>>();
    }

    std::vector<std::shared_ptr<NodeMetadata>>
    TreeOverlay::CalculateNodesToCollectAck(std::shared_ptr<AbstractMessage> message) {
        return this->GetNodeList();
    }

    const int TreeOverlay::GetBranch() const {
        return this->branch;
    }

    void TreeOverlay::SetBranch(int branch) {
        this->branch = branch;
    }

    const std::vector<std::shared_ptr<NodeMetadata>> &TreeOverlay::GetNodeList() const {
        return this->nodeList;
    }

    void TreeOverlay::SetNodeList(std::vector<std::shared_ptr<NodeMetadata>> nodeList) {
        this->nodeList = std::move(nodeList);
    }

    std::map<int, std::shared_ptr<CompleteTree>> &TreeOverlay::GetTrees() {
        return this->trees;
    }

    void TreeOverlay::SetTrees(std::map<int, std::shared_ptr<CompleteTree>> trees) {
        this->trees = std::move(trees);
    }

} // Ripple