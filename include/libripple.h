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

struct RippleNodeMetadata {
    int Id;
    char *Address;
    int Port;
};

struct RippleAbstractMessage {
    int Id;
};

void RippleLoggerInfo(const char *source, const char *format);
void *RippleCreateStarOverlay();
void *RippleCreateTreeOverlay(int branch);
void RippleBuildOverlay(void *overlay, struct RippleNodeMetadata *nodeList, int nodeCount);

// Returns the count of elements in the list. Results will be saved in the buffer.
int RippleCalculateNodesToSync(void *overlay, struct RippleNodeMetadata *buffer, struct RippleAbstractMessage *message,
                               struct RippleNodeMetadata *source,
                               struct RippleNodeMetadata *current);

// Returns the count of elements in the list. Results will be saved in the buffer.
int RippleCalculateNodesToCollectAck(void *overlay, struct RippleNodeMetadata *buffer, struct RippleAbstractMessage *message);

void RippleDeleteOverlay(void *overlay);

#ifdef __cplusplus
}
#endif

#endif //LIBRIPPLE_H
