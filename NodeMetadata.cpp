// Copyright (c) 2023 Institute of Software, Chinese Academy of Sciences
// libripple is licensed under Mulan PSL v2.
// You can use this software according to the terms and conditions of the Mulan PSL v2.
// You may obtain a copy of Mulan PSL v2 at:
//          http://license.coscl.org.cn/MulanPSL2
// THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
// EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
// MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
// See the Mulan PSL v2 for more details.

#include "NodeMetadata.h"

namespace Ripple {
    NodeMetadata::NodeMetadata() {

    }

    NodeMetadata::~NodeMetadata() {

    }

    NodeMetadata::NodeMetadata(int id, std::string address, int port) {
        this->SetId(id);
        this->SetAddress(address);
        this->SetPort(port);
    }

    const int NodeMetadata::GetId() const {
        return this->id;
    }

    void NodeMetadata::SetId(int id) {
        this->id = id;
    }

    const std::string &NodeMetadata::GetAddress() const {
        return this->address;
    }

    void NodeMetadata::SetAddress(std::string address) {
        this->address = std::move(address);
    }

    const int NodeMetadata::GetPort() const {
        return this->port;
    }

    void NodeMetadata::SetPort(int port) {
        this->port = port;
    }

} // Ripple