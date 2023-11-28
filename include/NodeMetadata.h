// Copyright (c) 2023 Institute of Software, Chinese Academy of Sciences
// libripple is licensed under Mulan PSL v2.
// You can use this software according to the terms and conditions of the Mulan PSL v2.
// You may obtain a copy of Mulan PSL v2 at:
//          http://license.coscl.org.cn/MulanPSL2
// THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
// EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
// MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
// See the Mulan PSL v2 for more details.

#ifndef LIBRIPPLE_NODEMETADATA_H
#define LIBRIPPLE_NODEMETADATA_H

#include <string>

namespace Ripple {
    namespace Common {
        namespace Entity {

            class NodeMetadata {
            public:
                NodeMetadata();

                NodeMetadata(int id, std::string address, int port);

                virtual ~NodeMetadata();

                NodeMetadata(const NodeMetadata &) = delete;

                NodeMetadata &operator=(const NodeMetadata &) = delete;

                const int GetId() const;

                void SetId(int id);

                const std::string &GetAddress() const;

                void SetAddress(std::string address);

                const int GetPort() const;

                void SetPort(int port);

            private:
                int id;
                std::string address;
                int port;
            };
        }
    }
} // Ripple

#endif //LIBRIPPLE_NODEMETADATA_H
