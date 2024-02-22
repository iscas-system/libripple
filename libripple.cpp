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
#include "Constants.h"
#include "UpdateMessage.h"
#include "DeleteMessage.h"
#include "IncrementalUpdateMessage.h"

#ifdef __cplusplus
extern "C" {
#endif

static void
convertList(RippleNodeMetadata *buffer, std::vector<std::shared_ptr<Ripple::Common::Entity::NodeMetadata>> &list);
static std::shared_ptr<Ripple::Common::Entity::AbstractMessage> convertMessageFromStruct(struct RippleMessage *message);

static void
convertList(RippleNodeMetadata *buffer, std::vector<std::shared_ptr<Ripple::Common::Entity::NodeMetadata>> &list) {
    int i = 0;
    for (i = 0; i < (int) list.size(); i++) {
        auto node = list.at(i);
        buffer[i].Id = node->GetId();
        buffer[i].Address = (char *) malloc(node->GetAddress().length() + 1);
        strcpy(buffer[i].Address, node->GetAddress().c_str());
        buffer[i].Port = node->GetPort();
    }
}

static std::shared_ptr<Ripple::Common::Entity::AbstractMessage>
convertMessageFromStruct(struct RippleMessage *message) {
    if (message != nullptr) {
        if (message->Type != nullptr) {
            std::shared_ptr<Ripple::Common::Entity::AbstractMessage> ret = nullptr;
            if (strcmp(message->Type, MESSAGE_TYPE_DELETE) == 0) {
                ret = std::make_shared<Ripple::Common::Entity::DeleteMessage>();
            } else if (strcmp(message->Type, MESSAGE_TYPE_UPDATE) == 0) {
                ret = std::make_shared<Ripple::Common::Entity::UpdateMessage>();
                auto p = std::dynamic_pointer_cast<Ripple::Common::Entity::UpdateMessage>(ret);
                if (message->Value != nullptr) {
                    p->SetValue(std::string(message->Value));
                }
            } else if (strcmp(message->Type, MESSAGE_TYPE_INCREMENTAL_UPDATE) == 0) {
                ret = std::make_shared<Ripple::Common::Entity::IncrementalUpdateMessage>();
                auto p = std::dynamic_pointer_cast<Ripple::Common::Entity::IncrementalUpdateMessage>(ret);
                if (message->Value != nullptr) {
                    p->SetValue(std::string(message->Value));
                }
                if (!uuid_is_null(message->BaseMessageUuid)) {
                    p->SetBaseMessageUuid(message->BaseMessageUuid);
                }
                if (message->AtomicOperation != nullptr) {
                    p->SetAtomicOperation(std::string(message->AtomicOperation));
                }
            } else {
                // Unknown type
                return nullptr;
            }
            if (!uuid_is_null(message->Uuid)) {
                ret->SetUuid(message->Uuid);
            }
            if (message->ApplicationName != nullptr) {
                ret->SetApplicationName(std::string(message->ApplicationName));
            }
            if (message->Key != nullptr) {
                ret->SetKey(std::string(message->Key));
            }
            ret->SetLastUpdate(message->LastUpdate);
            ret->SetLastUpdateServerId(message->LastUpdateServerId);
            return ret;
        }
    }
    return nullptr;
}

void RippleLoggerInfo(const char *source, const char *format) {
    Ripple::Common::Logger::Info(source, format);
}

void *RippleCreateStarOverlay() {
    return new Ripple::Server::Core::Overlay::StarOverlay();
}

void *RippleCreateTreeOverlay(int branch) {
    return new Ripple::Server::Core::Overlay::Tree::TreeOverlay(branch);
}

void RippleBuildOverlay(void *overlay, struct RippleNodeMetadata *nodeList, int nodeCount) {
    std::vector<std::shared_ptr<Ripple::Common::Entity::NodeMetadata>> list;
    int i = 0;
    for (i = 0; i < nodeCount; i++) {
        auto node = std::make_shared<Ripple::Common::Entity::NodeMetadata>(
                nodeList[i].Id, std::string(nodeList[i].Address), nodeList[i].Port);
        list.push_back(node);
    }
    ((Ripple::Server::Core::Overlay::Overlay *) overlay)->BuildOverlay(list);
}


int RippleCalculateNodesToSync(void *overlay, struct RippleNodeMetadata *buffer, struct RippleMessage *message,
                               struct RippleNodeMetadata *source,
                               struct RippleNodeMetadata *current) {
    auto sourceNode = std::make_shared<Ripple::Common::Entity::NodeMetadata>(
            source->Id, std::string(source->Address), source->Port);
    auto currentNode = std::make_shared<Ripple::Common::Entity::NodeMetadata>(
            current->Id, std::string(current->Address), current->Port);
    auto list = ((Ripple::Server::Core::Overlay::Overlay *) overlay)->CalculateNodesToSync(
            convertMessageFromStruct(message), sourceNode,
            currentNode);
    convertList(buffer, list);
    return (int) list.size();
}

int
RippleCalculateNodesToCollectAck(void *overlay, struct RippleNodeMetadata *buffer,
                                 struct RippleMessage *message) {
    auto list = ((Ripple::Server::Core::Overlay::Overlay *) overlay)->CalculateNodesToCollectAck(
            convertMessageFromStruct(message));
    convertList(buffer, list);
    return (int) list.size();
}

void RippleDeleteOverlay(void *overlay) {
    delete ((Ripple::Server::Core::Overlay::Overlay *) overlay);
}


#ifdef __cplusplus
}
#endif