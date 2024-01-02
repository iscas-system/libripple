// Copyright (c) 2023 Institute of Software, Chinese Academy of Sciences
// libripple is licensed under Mulan PSL v2.
// You can use this software according to the terms and conditions of the Mulan PSL v2.
// You may obtain a copy of Mulan PSL v2 at:
//          http://license.coscl.org.cn/MulanPSL2
// THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
// EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
// MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
// See the Mulan PSL v2 for more details.

#ifndef LIBRIPPLE_ACK_H
#define LIBRIPPLE_ACK_H

namespace Ripple {
    namespace Common {
        namespace Entity {
            class Ack {
            public:
                Ack();

                virtual ~Ack();

                Ack(const Ack &) = delete;

                Ack &operator=(const Ack &) = delete;
            };
        } // Entity
    } // Common
} // Ripple

#endif //LIBRIPPLE_ACK_H
