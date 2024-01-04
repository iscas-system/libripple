// Copyright (c) 2023 Institute of Software, Chinese Academy of Sciences
// libripple is licensed under Mulan PSL v2.
// You can use this software according to the terms and conditions of the Mulan PSL v2.
// You may obtain a copy of Mulan PSL v2 at:
//          http://license.coscl.org.cn/MulanPSL2
// THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
// EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
// MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
// See the Mulan PSL v2 for more details.

#ifndef LIBRIPPLE_ACKSERVICE_H
#define LIBRIPPLE_ACKSERVICE_H

// TODO: Implement this
#include <memory>
#include "Storage.h"

namespace Ripple {
    namespace Common {
        namespace Storage {
            class Storage;

            class AckService {
            public:
                explicit AckService(Storage *storage);

                virtual ~AckService();

                AckService(const AckService &) = delete;

                AckService &operator=(const AckService &) = delete;

            private:
                Storage *storage;
            };
        }
    }
}

#endif //LIBRIPPLE_ACKSERVICE_H
