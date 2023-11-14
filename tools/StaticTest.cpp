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

void TestStarOverlay() {
    std::vector<std::shared_ptr<Ripple::NodeMetadata>> list;
    auto nodeOne = std::make_shared<Ripple::NodeMetadata>(1, "192.168.1.1", 8080);
    auto nodeTwo = std::make_shared<Ripple::NodeMetadata>(2, "192.168.1.2", 8080);
    auto nodeThree = std::make_shared<Ripple::NodeMetadata>(3, "192.168.1.3", 8080);
    list.push_back(nodeOne);
    list.push_back(nodeTwo);
    list.push_back(nodeThree);
    std::unique_ptr<Ripple::Overlay> overlay(new Ripple::StarOverlay());
    overlay->BuildOverlay(list);
    overlay->CalculateNodesToSync(nullptr, nodeOne, nodeOne);
    overlay->CalculateNodesToSync(nullptr, nodeOne, nodeTwo);
    overlay->CalculateNodesToCollectAck(nullptr);
}

int main(int argc, char *argv[]) {
    Ripple::Logger::Info("StaticTest", "Entering main().");
    TestStarOverlay();
    return 0;
}
