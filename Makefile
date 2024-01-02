# libripple Makefile
# Author: Zhen Tang <tangzhen12@otcaix.iscas.ac.cn>
# Affiliation: Institute of Software, Chinese Academy of Sciences

CC=g++
GCC=gcc
LD=g++

RIPPLE_CC=$(QUIET_CC)$(CC)
RIPPLE_LD=$(QUIET_LD)$(LD)

CPPFLAGS=-g -Wall -Werror -std=c++11 -c -fpic
CFLAGS=-g -Wall -Werror -c -fpic
INCLUDE_FLAGS=-Iinclude/
LDFLAGS=-g -Wall -Werror

SHARED_FLAGS=-shared
LIBRIPPLE_FLAGS=-lripple
LIB_FLAGS=-lpthread -luuid

LIBRARY_PATH=/usr/lib64
INCLUDE_PATH=/usr/include
HEADER_FILE=include/libripple.h

CCCOLOR="\033[34;1m"
LINKCOLOR="\033[35;1m"
REMOVECOLOR="\033[31;1m"
INSTALLCOLOR="\033[32;1m"
SRCCOLOR="\033[33;1m"
BINCOLOR="\033[36;1m"
ENDCOLOR="\033[0m"

ifndef V
QUIET_CC = @echo -e $(CCCOLOR)"[COMPILE]   "$(ENDCOLOR)$(SRCCOLOR)$@$(ENDCOLOR) 1>&2;
QUIET_LD = @echo -e $(LINKCOLOR)"[LINK]      "$(ENDCOLOR)$(BINCOLOR)$@$(ENDCOLOR) 1>&2;
QUIET_CLEAN = echo -e $(REMOVECOLOR)"[REMOVE]    "$(ENDCOLOR)$(BINCOLOR)$$toRemove$(ENDCOLOR) 1>&2;
endif

# Releases
STATIC_TEST_OBJECTS = output/StaticTest.o
DYNAMIC_TEST_OBJECTS = output/DynamicTest.o
TARGETS = release/libripple.so release/StaticTest release/DynamicTest release/GoTest

# Objects
LIBRIPPLE_OBJECTS += output/NodeMetadata.o output/Ack.o output/ClientMetadata.o output/Item.o output/SystemInfo.o
LIBRIPPLE_OBJECTS += output/AbstractMessage.o output/UpdateMessage.o output/IncrementalUpdateMessage.o output/DeleteMessage.o
LIBRIPPLE_OBJECTS += output/Overlay.o output/StarOverlay.o output/HashingBasedOverlay.o output/GossipOverlay.o output/ExpanderOverlay.o
LIBRIPPLE_OBJECTS += output/TreeOverlay.o output/TreeNode.o output/CompleteTree.o
LIBRIPPLE_OBJECTS += output/Logger.o
LIBRIPPLE_OBJECTS += output/libripple.o

.PHONY: all prepare clean install

all: prepare $(TARGETS) install

clean:
	@for toRemove in $(STATIC_TEST_OBJECTS) $(DYNAMIC_TEST_OBJECTS) $(LIBRIPPLE_OBJECTS) $(TARGETS); \
    do \
    $(QUIET_CLEAN)rm -f $$toRemove; \
    done
	@if [ -d "output" ];then rmdir output; fi
	@if [ -d "release" ];then rmdir release; fi

prepare:
	@mkdir -p output
	@mkdir -p release

install: release/libripple.so $(HEADER_FILE) prepare
	@echo -e $(INSTALLCOLOR)"[INSTALL]   "$(ENDCOLOR)$(BINCOLOR)$<$(ENDCOLOR);
	@cp -f release/libripple.so $(LIBRARY_PATH)
	@echo -e $(INSTALLCOLOR)"[INSTALL]   "$(ENDCOLOR)$(BINCOLOR)$(HEADER_FILE)$(ENDCOLOR);
	@cp -f $(HEADER_FILE) $(INCLUDE_PATH)
	@ldconfig

release/libripple.so: $(LIBRIPPLE_OBJECTS)
	$(RIPPLE_LD) $(LDFLAGS) $(SHARED_FLAGS) $(LIB_FLAGS) -o $@ $^

output/libripple.o: libripple.cpp include/libripple.h
	$(RIPPLE_CC) $(CPPFLAGS) $(INCLUDE_FLAGS) -o $@ $<

release/StaticTest: output/StaticTest.o $(LIBRIPPLE_OBJECTS)
	$(RIPPLE_LD) $(LDFLAGS) $(LIB_FLAGS) -o $@ $^

output/StaticTest.o: test/StaticTest.cpp
	$(RIPPLE_CC) $(CPPFLAGS) -o $@ $<

release/DynamicTest: output/DynamicTest.o install
	$(RIPPLE_LD) $(LDFLAGS) $(LIB_FLAGS) $(LIBRIPPLE_FLAGS) -o $@ $<

output/DynamicTest.o: test/DynamicTest.c install
	$(QUIET_CC)$(GCC) $(CFLAGS) -o $@ $<

release/GoTest: test/GoTest.go install
	$(QUIET_CC)go build -o $@ $<

output/NodeMetadata.o: NodeMetadata.cpp include/NodeMetadata.h
	$(RIPPLE_CC) $(CPPFLAGS) $(INCLUDE_FLAGS) -o $@ $<

output/Ack.o: Ack.cpp include/Ack.h
	$(RIPPLE_CC) $(CPPFLAGS) $(INCLUDE_FLAGS) -o $@ $<

output/ClientMetadata.o: ClientMetadata.cpp include/ClientMetadata.h
	$(RIPPLE_CC) $(CPPFLAGS) $(INCLUDE_FLAGS) -o $@ $<

output/Item.o: Item.cpp include/Item.h
	$(RIPPLE_CC) $(CPPFLAGS) $(INCLUDE_FLAGS) -o $@ $<

output/SystemInfo.o: SystemInfo.cpp include/SystemInfo.h
	$(RIPPLE_CC) $(CPPFLAGS) $(INCLUDE_FLAGS) -o $@ $<

output/AbstractMessage.o: AbstractMessage.cpp include/AbstractMessage.h
	$(RIPPLE_CC) $(CPPFLAGS) $(INCLUDE_FLAGS) -o $@ $<

output/UpdateMessage.o: UpdateMessage.cpp include/UpdateMessage.h include/Constants.h
	$(RIPPLE_CC) $(CPPFLAGS) $(INCLUDE_FLAGS) -o $@ $<

output/IncrementalUpdateMessage.o: IncrementalUpdateMessage.cpp include/IncrementalUpdateMessage.h include/Constants.h
	$(RIPPLE_CC) $(CPPFLAGS) $(INCLUDE_FLAGS) -o $@ $<

output/DeleteMessage.o: DeleteMessage.cpp include/DeleteMessage.h include/Constants.h
	$(RIPPLE_CC) $(CPPFLAGS) $(INCLUDE_FLAGS) -o $@ $<

output/Overlay.o: Overlay.cpp include/Overlay.h
	$(RIPPLE_CC) $(CPPFLAGS) $(INCLUDE_FLAGS) -o $@ $<

output/TreeOverlay.o: TreeOverlay.cpp include/TreeOverlay.h
	$(RIPPLE_CC) $(CPPFLAGS) $(INCLUDE_FLAGS) -o $@ $<

output/TreeNode.o: TreeNode.cpp include/TreeNode.h
	$(RIPPLE_CC) $(CPPFLAGS) $(INCLUDE_FLAGS) -o $@ $<

output/CompleteTree.o: CompleteTree.cpp include/CompleteTree.h
	$(RIPPLE_CC) $(CPPFLAGS) $(INCLUDE_FLAGS) -o $@ $<

output/HashingBasedOverlay.o: HashingBasedOverlay.cpp include/HashingBasedOverlay.h
	$(RIPPLE_CC) $(CPPFLAGS) $(INCLUDE_FLAGS) -o $@ $<

output/StarOverlay.o: StarOverlay.cpp include/StarOverlay.h
	$(RIPPLE_CC) $(CPPFLAGS) $(INCLUDE_FLAGS) -o $@ $<

output/GossipOverlay.o: GossipOverlay.cpp include/GossipOverlay.h
	$(RIPPLE_CC) $(CPPFLAGS) $(INCLUDE_FLAGS) -o $@ $<

output/ExpanderOverlay.o: ExpanderOverlay.cpp include/ExpanderOverlay.h
	$(RIPPLE_CC) $(CPPFLAGS) $(INCLUDE_FLAGS) -o $@ $<

output/Logger.o: Logger.cpp include/Logger.h
	$(RIPPLE_CC) $(CPPFLAGS) $(INCLUDE_FLAGS) -o $@ $<

