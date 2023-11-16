// Copyright (c) 2023 Institute of Software, Chinese Academy of Sciences
// libripple is licensed under Mulan PSL v2.
// You can use this software according to the terms and conditions of the Mulan PSL v2.
// You may obtain a copy of Mulan PSL v2 at:
//          http://license.coscl.org.cn/MulanPSL2
// THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
// EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
// MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
// See the Mulan PSL v2 for more details.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libripple.h>

#define NODE_COUNT 10

int main(int argc, char *argv[]) {
    RippleLoggerInfo("DynamicTest", "main(): Hello, world.");

    struct RippleNodeMetadata nodeList[NODE_COUNT];
    struct RippleNodeMetadata buffer[NODE_COUNT];

    int stringLength = strlen("192.168.1.1");
    int i = 0;
    for (i = 0; i < NODE_COUNT; i++) {
        nodeList[i].Id = i + 1;
        nodeList[i].Address = (char *) malloc(stringLength + 1);
        strcpy(nodeList[i].Address, "192.168.1.1");
        nodeList[i].Port = 8080;
    }

    void *overlay = RippleCreateStarOverlay();
    RippleBuildOverlay(overlay, nodeList, NODE_COUNT);
    int count = RippleCalculateNodesToSync(overlay, buffer, NULL, &(nodeList[0]), &(nodeList[0]));
    printf("RippleCalculateNodesToSync() count = %d\n", count);
    count = RippleCalculateNodesToCollectAck(overlay, buffer, NULL);
    printf("RippleCalculateNodesToCollectAck() count = %d\n", count);
    RippleDeleteOverlay(overlay);

    overlay = RippleCreateTreeOverlay(3);
    RippleBuildOverlay(overlay, nodeList, NODE_COUNT);
    count = RippleCalculateNodesToSync(overlay, buffer, NULL, &(nodeList[0]), &(nodeList[0]));
    printf("RippleCalculateNodesToSync() count = %d\n", count);
    count = RippleCalculateNodesToCollectAck(overlay, buffer, NULL);
    printf("RippleCalculateNodesToCollectAck() count = %d\n", count);
    RippleDeleteOverlay(overlay);

    for (i = 0; i < NODE_COUNT; i++) {
        free(nodeList[i].Address);
    }
    return 0;
}
