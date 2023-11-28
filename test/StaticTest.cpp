// Copyright (c) 2023 Institute of Software, Chinese Academy of Sciences
// libripple is licensed under Mulan PSL v2.
// You can use this software according to the terms and conditions of the Mulan PSL v2.
// You may obtain a copy of Mulan PSL v2 at:
//          http://license.coscl.org.cn/MulanPSL2
// THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
// EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
// MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
// See the Mulan PSL v2 for more details.

#include <memory>

#include "../include/Logger.h"
#include "../include/NodeMetadata.h"
#include "../include/StarOverlay.h"
#include "../include/CompleteTree.h"
#include "../include/TreeOverlay.h"

void AssertEquals(int expected, int actual) {
    if (expected != actual) {
        Ripple::Common::Logger::Info("Assert", "Assertion failed: expected: %d, actual: %d.", expected, actual);
    }
}

void TestStarOverlay() {
    std::vector<std::shared_ptr<Ripple::Common::Entity::NodeMetadata>> list;
    auto nodeOne = std::make_shared<Ripple::Common::Entity::NodeMetadata>(1, "192.168.1.1", 8080);
    auto nodeTwo = std::make_shared<Ripple::Common::Entity::NodeMetadata>(2, "192.168.1.2", 8080);
    auto nodeThree = std::make_shared<Ripple::Common::Entity::NodeMetadata>(3, "192.168.1.3", 8080);
    list.push_back(nodeOne);
    list.push_back(nodeTwo);
    list.push_back(nodeThree);
    std::unique_ptr<Ripple::Server::Core::Overlay::Overlay> overlay(new Ripple::Server::Core::Overlay::StarOverlay());
    overlay->BuildOverlay(list);
    auto ret = overlay->CalculateNodesToSync(nullptr, nodeOne, nodeOne);
    AssertEquals(2, ret.size());
    ret = overlay->CalculateNodesToSync(nullptr, nodeOne, nodeTwo);
    AssertEquals(0, ret.size());
    overlay->CalculateNodesToCollectAck(nullptr);
}

void TestCompleteTree() {
    int branch = 3;
    int nodeCount = 10;
    int i = 0;
    std::vector<std::shared_ptr<Ripple::Common::Entity::NodeMetadata>> nodeList;
    for (i = 0; i < nodeCount; i++) {
        nodeList.push_back(std::make_shared<Ripple::Common::Entity::NodeMetadata>(i + 1, "test", 0));
    }

    Ripple::Server::Core::Overlay::Tree::CompleteTree completeTree(branch, nodeList);
    auto root = completeTree.GetRoot();
    AssertEquals(1, root->GetNodeMetadata()->GetId());

    AssertEquals(3, root->GetChildren().size());
    AssertEquals(2, root->GetChildren().at(0)->GetNodeMetadata()->GetId());
    AssertEquals(3, root->GetChildren().at(1)->GetNodeMetadata()->GetId());
    AssertEquals(4, root->GetChildren().at(2)->GetNodeMetadata()->GetId());

    AssertEquals(3, root->GetChildren().at(0)->GetChildren().size());
    AssertEquals(5, root->GetChildren().at(0)->GetChildren().at(0)->GetNodeMetadata()->GetId());
    AssertEquals(6, root->GetChildren().at(0)->GetChildren().at(1)->GetNodeMetadata()->GetId());
    AssertEquals(7, root->GetChildren().at(0)->GetChildren().at(2)->GetNodeMetadata()->GetId());

    AssertEquals(3, root->GetChildren().at(1)->GetChildren().size());
    AssertEquals(8, root->GetChildren().at(1)->GetChildren().at(0)->GetNodeMetadata()->GetId());
    AssertEquals(9, root->GetChildren().at(1)->GetChildren().at(1)->GetNodeMetadata()->GetId());
    AssertEquals(10, root->GetChildren().at(1)->GetChildren().at(2)->GetNodeMetadata()->GetId());
}

void TestTreeOverlay() {
    int branch = 3;
    int nodeCount = 10;
    int i = 0;
    std::vector<std::shared_ptr<Ripple::Common::Entity::NodeMetadata>> nodeList;
    for (i = 0; i < nodeCount; i++) {
        nodeList.push_back(std::make_shared<Ripple::Common::Entity::NodeMetadata>(i + 1, "test", 0));
    }

    Ripple::Server::Core::Overlay::Tree::TreeOverlay treeOverlay(branch);
    treeOverlay.BuildOverlay(nodeList);
    auto list = treeOverlay.CalculateNodesToSync(nullptr, nodeList.at(0), nodeList.at(2));
    AssertEquals(3, list.size());
    AssertEquals(8, list.at(0)->GetId());
    AssertEquals(9, list.at(1)->GetId());
    AssertEquals(10, list.at(2)->GetId());

    list = treeOverlay.CalculateNodesToSync(nullptr, nodeList.at(2), nodeList.at(0));
    AssertEquals(0, list.size());
}


int main(int argc, char *argv[]) {
    TestStarOverlay();
    TestCompleteTree();
    TestTreeOverlay();
    return 0;
}
