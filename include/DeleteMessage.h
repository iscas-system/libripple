// Copyright (c) 2023 Institute of Software, Chinese Academy of Sciences
// libripple is licensed under Mulan PSL v2.
// You can use this software according to the terms and conditions of the Mulan PSL v2.
// You may obtain a copy of Mulan PSL v2 at:
//          http://license.coscl.org.cn/MulanPSL2
// THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
// EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
// MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
// See the Mulan PSL v2 for more details.

#ifndef LIBRIPPLE_DELETEMESSAGE_H
#define LIBRIPPLE_DELETEMESSAGE_H

#include "AbstractMessage.h"

namespace Ripple {
    namespace Common {
        namespace Entity {

            class DeleteMessage final : public AbstractMessage {
            public:
                DeleteMessage();

                DeleteMessage(uuid_t uuid, std::string applicationName, std::string key, time_t lastUpdate,
                              int lastUpdateServerId);

                DeleteMessage(std::string applicationName, std::string key, time_t lastUpdate, int lastUpdateServerId);

                ~DeleteMessage() final;

                DeleteMessage(const DeleteMessage &) = delete;

                DeleteMessage &operator=(const DeleteMessage &) = delete;
            };
        }
    }
}
#endif //LIBRIPPLE_DELETEMESSAGE_H
