// Copyright (c) 2023 Institute of Software, Chinese Academy of Sciences
// libripple is licensed under Mulan PSL v2.
// You can use this software according to the terms and conditions of the Mulan PSL v2.
// You may obtain a copy of Mulan PSL v2 at:
//          http://license.coscl.org.cn/MulanPSL2
// THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
// EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
// MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
// See the Mulan PSL v2 for more details.

#include <cstring>

#include "libripple.h"
#include "Logger.h"
#include "StarOverlay.h"
#include "TreeOverlay.h"


#ifdef __cplusplus
extern "C" {
#endif

void convertList(RippleNodeMetadata *buffer, std::vector<std::shared_ptr<Ripple::NodeMetadata>> &list);
std::shared_ptr<Ripple::AbstractMessage> convertMessageFromStruct(struct RippleAbstractMessage *message);

void convertList(RippleNodeMetadata *buffer, std::vector<std::shared_ptr<Ripple::NodeMetadata>> &list) {
    int i = 0;
    for (i = 0; i < (int) list.size(); i++) {
        auto node = list.at(i);
        buffer[i].Id = node->GetId();
        buffer[i].Address = (char *) malloc(node->GetAddress().length() + 1);
        strcpy(buffer[i].Address, node->GetAddress().c_str());
        buffer[i].Port = node->GetPort();
    }
}

std::shared_ptr<Ripple::AbstractMessage> convertMessageFromStruct(struct RippleAbstractMessage *message) {
    // TODO: Extract information from API input
    return std::make_shared<Ripple::AbstractMessage>();
}

void RippleLoggerInfo(const char *source, const char *format) {
    Ripple::Logger::Info(source, format);
}

void *RippleCreateStarOverlay() {
    return new Ripple::StarOverlay();
}

void *RippleCreateTreeOverlay(int branch) {
    return new Ripple::TreeOverlay(branch);
}

void RippleBuildOverlay(void *overlay, struct RippleNodeMetadata *nodeList, int nodeCount) {
    std::vector<std::shared_ptr<Ripple::NodeMetadata>> list;
    int i = 0;
    for (i = 0; i < nodeCount; i++) {
        auto node = std::make_shared<Ripple::NodeMetadata>(
                nodeList[i].Id, std::string(nodeList[i].Address), nodeList[i].Port);
        list.push_back(node);
    }
    ((Ripple::Overlay *) overlay)->BuildOverlay(list);
}


int RippleCalculateNodesToSync(void *overlay, struct RippleNodeMetadata *buffer, struct RippleAbstractMessage *message,
                               struct RippleNodeMetadata *source,
                               struct RippleNodeMetadata *current) {
    auto sourceNode = std::make_shared<Ripple::NodeMetadata>(
            source->Id, std::string(source->Address), source->Port);
    auto currentNode = std::make_shared<Ripple::NodeMetadata>(
            current->Id, std::string(current->Address), current->Port);
    auto list = ((Ripple::Overlay *) overlay)->CalculateNodesToSync(convertMessageFromStruct(message), sourceNode,
                                                                    currentNode);
    convertList(buffer, list);
    return (int) list.size();
}

int
RippleCalculateNodesToCollectAck(void *overlay, struct RippleNodeMetadata *buffer,
                                 struct RippleAbstractMessage *message) {
    auto list = ((Ripple::Overlay *) overlay)->CalculateNodesToCollectAck(convertMessageFromStruct(message));
    convertList(buffer, list);
    return (int) list.size();
}

void RippleDeleteOverlay(void *overlay) {
    delete ((Ripple::Overlay *) overlay);
}


#ifdef __cplusplus
}
#endif