// Copyright (c) 2023 Institute of Software, Chinese Academy of Sciences
// libripple is licensed under Mulan PSL v2.
// You can use this software according to the terms and conditions of the Mulan PSL v2.
// You may obtain a copy of Mulan PSL v2 at:
//          http://license.coscl.org.cn/MulanPSL2
// THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
// EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
// MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
// See the Mulan PSL v2 for more details.

#ifndef LIBRIPPLE_UPDATEMESSAGE_H
#define LIBRIPPLE_UPDATEMESSAGE_H

#include "AbstractMessage.h"

namespace Ripple {
    namespace Common {
        namespace Entity {

            class UpdateMessage final : public AbstractMessage {
            public:
                UpdateMessage();

                UpdateMessage(std::string applicationName, std::string key, std::string value, time_t lastUpdate,
                              int lastUpdateServerId);

                UpdateMessage(uuid_t uuid, std::string applicationName, std::string key, std::string value,
                              time_t lastUpdate, int lastUpdateServerId);

                ~UpdateMessage() final;

                UpdateMessage(const UpdateMessage &) = delete;

                UpdateMessage &operator=(const UpdateMessage &) = delete;

                const std::string &GetValue() const;

                void SetValue(std::string value);

            private:
                std::string value;

            };
        }
    }
}

#endif //LIBRIPPLE_UPDATEMESSAGE_H
