// Copyright (c) 2023 Institute of Software, Chinese Academy of Sciences
// libripple is licensed under Mulan PSL v2.
// You can use this software according to the terms and conditions of the Mulan PSL v2.
// You may obtain a copy of Mulan PSL v2 at:
//          http://license.coscl.org.cn/MulanPSL2
// THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
// EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
// MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
// See the Mulan PSL v2 for more details.

#ifndef LIBRIPPLE_H
#define LIBRIPPLE_H

#ifdef __cplusplus
extern "C" {
#endif

#include <time.h>
#include <uuid/uuid.h>

struct RippleNodeMetadata {
    int Id;
    char *Address;
    int Port;
};

struct RippleMessage {
    uuid_t Uuid;
    char *Type;
    char *ApplicationName;
    char *Key;
    time_t LastUpdate;
    int LastUpdateServerId;

    // For UpdateMessage and IncrementalUpdateMessage
    char *Value;

    // For IncrementalUpdateMessage
    uuid_t BaseMessageUuid;
    char *AtomicOperation;
};

void RippleLoggerInfo(const char *source, const char *format);
void *RippleCreateStarOverlay();
void *RippleCreateTreeOverlay(int branch);
void RippleBuildOverlay(void *overlay, struct RippleNodeMetadata *nodeList, int nodeCount);

// Returns the count of elements in the list. Results will be saved in the buffer.
// The caller needs to allocate and clean up the structs used.
int RippleCalculateNodesToSync(void *overlay, struct RippleNodeMetadata *buffer, struct RippleMessage *message,
                               struct RippleNodeMetadata *source, struct RippleNodeMetadata *current);

// Returns the count of elements in the list.
// Results will be saved in the buffer.
// The caller needs to allocate and clean up the structs used.
int RippleCalculateNodesToCollectAck(void *overlay, struct RippleNodeMetadata *buffer, struct RippleMessage *message);

void RippleDeleteOverlay(void *overlay);

#ifdef __cplusplus
}
#endif

#endif //LIBRIPPLE_H
