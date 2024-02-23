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
#include <iostream>
#include <ctime>

#include "../include/Logger.h"
#include "../include/NodeMetadata.h"
#include "../include/StarOverlay.h"
#include "../include/CompleteTree.h"
#include "../include/TreeOverlay.h"
#include "../include/DeleteMessage.h"
#include "../include/UpdateMessage.h"
#include "../include/IncrementalUpdateMessage.h"
#include "../include/Constants.h"
#include "../include/Storage.h"

void PrintUpdateMessage(Ripple::Common::Entity::UpdateMessage *updateMessage) {
    char uuidStr[37] = {0};
    uuid_unparse(updateMessage->GetUuid(), uuidStr);
    std::cout
            << "[UpdateMessage] " << "uuid = " << uuidStr << ", " << "type = " << updateMessage->GetType() << ", "
            << "application name = " << updateMessage->GetApplicationName() << ", "
            << "key = " << updateMessage->GetKey() << "," << "value = " << updateMessage->GetValue() << ","
            << "last update = " << updateMessage->GetLastUpdate() << ","
            << "last update server id = " << updateMessage->GetLastUpdateServerId() << std::endl;
}

void PrintDeleteMessage(Ripple::Common::Entity::DeleteMessage *deleteMessage) {
    char uuidStr[37] = {0};
    uuid_unparse(deleteMessage->GetUuid(), uuidStr);
    std::cout
            << "[DeleteMessage] " << "uuid = " << uuidStr << ", " << "type = " << deleteMessage->GetType() << ", "
            << "application name = " << deleteMessage->GetApplicationName() << ", "
            << "key = " << deleteMessage->GetKey() << ","
            << "last update = " << deleteMessage->GetLastUpdate() << ","
            << "last update server id = " << deleteMessage->GetLastUpdateServerId() << std::endl;
}

void PrintIncrementalUpdateMessage(Ripple::Common::Entity::IncrementalUpdateMessage *incrementalUpdateMessage) {
    char uuidStr[37] = {0};
    uuid_unparse(incrementalUpdateMessage->GetUuid(), uuidStr);
    char baseMessageUuidStr[37] = {0};
    uuid_unparse(incrementalUpdateMessage->GetBaseMessageUuid(), baseMessageUuidStr);
    std::cout
            << "[IncrementalUpdateMessage] " << "uuid = " << uuidStr << ", " << "type = "
            << incrementalUpdateMessage->GetType() << ", "
            << "application name = " << incrementalUpdateMessage->GetApplicationName() << ", "
            << "key = " << incrementalUpdateMessage->GetKey() << ","
            << "base message uuid = " << baseMessageUuidStr << ", "
            << "atomic operation = " << incrementalUpdateMessage->GetAtomicOperation() << ", "
            << "value = " << incrementalUpdateMessage->GetValue() << ","
            << "last update = " << incrementalUpdateMessage->GetLastUpdate() << ","
            << "last update server id = " << incrementalUpdateMessage->GetLastUpdateServerId() << std::endl;
}

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
    const auto &root = completeTree.GetRoot();
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

void TestGenerateDeleteMessage() {
    Ripple::Common::Entity::DeleteMessage deleteMessage("testApp", "testKey", time(nullptr), 1);
    char uuidStr[37];
    uuid_unparse(deleteMessage.GetUuid(), uuidStr);
    std::cout << uuidStr << "," << deleteMessage.GetType() << "," << deleteMessage.GetApplicationName() << ","
              << deleteMessage.GetKey() << "," << deleteMessage.GetLastUpdate() << ","
              << deleteMessage.GetLastUpdateServerId() << std::endl;

    uuid_t uuid2;
    uuid_generate(uuid2);
    Ripple::Common::Entity::DeleteMessage deleteMessage2(uuid2, "testApp2", "testKey2", time(nullptr), 2);
    uuid_unparse(deleteMessage2.GetUuid(), uuidStr);
    std::cout << uuidStr << "," << deleteMessage2.GetType() << "," << deleteMessage2.GetApplicationName() << ","
              << deleteMessage2.GetKey() << "," << deleteMessage2.GetLastUpdate() << ","
              << deleteMessage2.GetLastUpdateServerId() << std::endl;
}

void TestGenerateUpdateMessage() {
    Ripple::Common::Entity::UpdateMessage updateMessage("testApp", "testKey", "testValue", time(nullptr), 1);
    char uuidStr[37];
    uuid_unparse(updateMessage.GetUuid(), uuidStr);
    std::cout << uuidStr << "," << updateMessage.GetType() << "," << updateMessage.GetApplicationName() << ","
              << updateMessage.GetKey() << "," << updateMessage.GetValue() << "," << updateMessage.GetLastUpdate()
              << "," << updateMessage.GetLastUpdateServerId() << std::endl;

    uuid_t uuid2;
    uuid_generate(uuid2);
    Ripple::Common::Entity::UpdateMessage updateMessage2(uuid2, "testApp2", "testKey2", "testValue2", time(nullptr), 2);
    uuid_unparse(updateMessage2.GetUuid(), uuidStr);
    std::cout << uuidStr << "," << updateMessage2.GetType() << "," << updateMessage2.GetApplicationName() << ","
              << updateMessage2.GetKey() << "," << updateMessage2.GetValue() << "," << updateMessage2.GetLastUpdate()
              << "," << updateMessage2.GetLastUpdateServerId() << std::endl;
}

void TestGenerateIncrementalUpdateMessage() {
    uuid_t baseMessageUuid;
    uuid_generate(baseMessageUuid);
    Ripple::Common::Entity::IncrementalUpdateMessage incrementalUpdateMessage("testApp", "testKey", baseMessageUuid,
                                                                              ATOMIC_OPERATION_ADD_ENTRY,
                                                                              "testValue",
                                                                              time(nullptr), 1);
    char uuidStr[37];
    uuid_unparse(incrementalUpdateMessage.GetUuid(), uuidStr);
    std::cout << uuidStr << "," << incrementalUpdateMessage.GetType() << ","
              << incrementalUpdateMessage.GetApplicationName() << ","
              << incrementalUpdateMessage.GetKey() << "," << incrementalUpdateMessage.GetValue() << ","
              << incrementalUpdateMessage.GetAtomicOperation() << "," << incrementalUpdateMessage.GetLastUpdate()
              << "," << incrementalUpdateMessage.GetLastUpdateServerId() << std::endl;

    uuid_t uuid2;
    uuid_generate(uuid2);
    uuid_generate(baseMessageUuid);
    Ripple::Common::Entity::IncrementalUpdateMessage incrementalUpdateMessage2(uuid2, "testApp2", "testKey2",
                                                                               baseMessageUuid,
                                                                               ATOMIC_OPERATION_REMOVE_ENTRY,
                                                                               "testValue2",
                                                                               time(nullptr), 2);
    uuid_unparse(incrementalUpdateMessage2.GetUuid(), uuidStr);
    std::cout << uuidStr << "," << incrementalUpdateMessage2.GetType() << ","
              << incrementalUpdateMessage2.GetApplicationName() << ","
              << incrementalUpdateMessage2.GetKey() << "," << incrementalUpdateMessage2.GetValue() << ","
              << incrementalUpdateMessage.GetAtomicOperation() << "," << incrementalUpdateMessage2.GetLastUpdate()
              << "," << incrementalUpdateMessage2.GetLastUpdateServerId() << std::endl;
}

void TestDatabase() {
    Ripple::Common::Storage::Storage storage("test.db");
    std::cout << storage.GetItemService()->NewItem("test", "test") << std::endl;
    std::cout << storage.GetItemService()->NewItem("test", "test1") << std::endl;
    std::cout << storage.GetItemService()->NewItem("test1", "test") << std::endl;

    auto item = storage.GetItemService()->GetItem("test", "test");
    if (item != nullptr) {
        std::cout << "Item: " << item->GetApplicationName() << "," << item->GetKey() << std::endl;
    }
    auto itemList = storage.GetItemService()->GetAllItems();
    for (auto iter = itemList.begin(); iter != itemList.end(); iter++) {
        std::cout << "ItemList.Item: " << (*iter)->GetApplicationName() << "," << (*iter)->GetKey() << std::endl;
    }

    std::cout << storage.GetItemService()->NewItem("testApp", "testKey") << std::endl;

    auto updateMessage = std::make_shared<Ripple::Common::Entity::UpdateMessage>("testApp", "testKey", "testValue",
                                                                                 time(nullptr), 1);
    std::cout << "New update message: " << storage.GetMessageService()->NewMessage(updateMessage) << std::endl;
    std::cout << "New update message: " << storage.GetMessageService()->NewMessage(updateMessage) << std::endl;
    std::cout << "Message exist:" << storage.GetMessageService()->Exist(updateMessage->GetUuid()) << std::endl;

    auto getUpdateMessage = std::dynamic_pointer_cast<Ripple::Common::Entity::UpdateMessage>(
            storage.GetMessageService()->GetMessageByUuid(updateMessage->GetUuid()));
    PrintUpdateMessage(getUpdateMessage.get());

    auto deleteMessage = std::make_shared<Ripple::Common::Entity::DeleteMessage>("testApp", "testKey", time(nullptr),
                                                                                 1);
    std::cout << "New delete message: " << storage.GetMessageService()->NewMessage(deleteMessage) << std::endl;
    std::cout << "New delete message: " << storage.GetMessageService()->NewMessage(deleteMessage) << std::endl;
    std::cout << "Message exist:" << storage.GetMessageService()->Exist(deleteMessage->GetUuid()) << std::endl;

    auto getDeleteMessage = std::dynamic_pointer_cast<Ripple::Common::Entity::DeleteMessage>(
            storage.GetMessageService()->GetMessageByUuid(deleteMessage->GetUuid()));
    PrintDeleteMessage(getDeleteMessage.get());

    uuid_t baseMessageUuid;
    uuid_generate(baseMessageUuid);
    auto incrementalUpdateMessage = std::make_shared<Ripple::Common::Entity::IncrementalUpdateMessage>("testApp",
                                                                                                       "testKey",
                                                                                                       baseMessageUuid,
                                                                                                       ATOMIC_OPERATION_ADD_ENTRY,
                                                                                                       "testValue",
                                                                                                       time(nullptr),
                                                                                                       1);
    std::cout << "New incremental update message: " << storage.GetMessageService()->NewMessage(incrementalUpdateMessage)
              << std::endl;
    std::cout << "New incremental update message: " << storage.GetMessageService()->NewMessage(incrementalUpdateMessage)
              << std::endl;
    std::cout << "Message exist:" << storage.GetMessageService()->Exist(incrementalUpdateMessage->GetUuid())
              << std::endl;

    auto getIncrementalUpdateMessage = std::dynamic_pointer_cast<Ripple::Common::Entity::IncrementalUpdateMessage>(
            storage.GetMessageService()->GetMessageByUuid(incrementalUpdateMessage->GetUuid()));
    PrintIncrementalUpdateMessage(getIncrementalUpdateMessage.get());

    auto ret = storage.GetMessageService()->FindMessages("testApp", "testKey");
    for (auto it = ret.begin(); it != ret.end(); it++) {
        if ((*it)->GetType() == MESSAGE_TYPE_UPDATE) {
            PrintUpdateMessage(std::dynamic_pointer_cast<Ripple::Common::Entity::UpdateMessage>(*it).get());
        } else if ((*it)->GetType() == MESSAGE_TYPE_DELETE) {
            PrintDeleteMessage(std::dynamic_pointer_cast<Ripple::Common::Entity::DeleteMessage>(*it).get());
        } else if ((*it)->GetType() == MESSAGE_TYPE_INCREMENTAL_UPDATE) {
            PrintIncrementalUpdateMessage(
                    std::dynamic_pointer_cast<Ripple::Common::Entity::IncrementalUpdateMessage>(*it).get());
        }
    }


    std::set<int> s;
    s.insert(1);
    s.insert(2);
    s.insert(3);
    storage.GetAckService()->InitializeAck(incrementalUpdateMessage->GetUuid(), s);
    storage.GetAckService()->RecordAck(incrementalUpdateMessage->GetUuid(), 1);
    auto ack = storage.GetAckService()->GetAck(incrementalUpdateMessage->GetUuid());
    char uuidStr[37];
    uuid_unparse(ack->GetMessageUuid(), uuidStr);
    std::cout << "ACK: uuid = " << uuidStr << ", Node list = ";
    for (auto elem: ack->GetNodeList()) {
        std::cout << elem << " ";
    }
    std::cout << ", Ack nodes = ";
    for (auto elem: ack->GetAckNodes()) {
        std::cout << elem << " ";
    }
    std::cout << std::endl;

    storage.GetAckService()->RecordAck(incrementalUpdateMessage->GetUuid(), 2);
    std::cout << "Get all acks" << std::endl;
    auto ackList = storage.GetAckService()->GetAllAcks();
    for (auto a: ackList) {
        char u[37];
        uuid_unparse(a->GetMessageUuid(), u);
        std::cout << "-> ACK: uuid = " << u << ", Node list = ";
        for (auto elem: a->GetNodeList()) {
            std::cout << elem << " ";
        }
        std::cout << ", Ack nodes = ";
        for (auto elem: a->GetAckNodes()) {
            std::cout << elem << " ";
        }
        std::cout << std::endl;
    }

}

int main(int argc, char *argv[]) {
    TestGenerateDeleteMessage();
    TestGenerateUpdateMessage();
    TestGenerateIncrementalUpdateMessage();
    TestStarOverlay();
    TestCompleteTree();
    TestTreeOverlay();
    TestDatabase();
    return 0;
}
