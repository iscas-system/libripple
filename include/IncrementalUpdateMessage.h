// Copyright (c) 2023 Institute of Software, Chinese Academy of Sciences
// libripple is licensed under Mulan PSL v2.
// You can use this software according to the terms and conditions of the Mulan PSL v2.
// You may obtain a copy of Mulan PSL v2 at:
//          http://license.coscl.org.cn/MulanPSL2
// THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
// EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
// MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
// See the Mulan PSL v2 for more details.

#ifndef LIBRIPPLE_INCREMENTALUPDATEMESSAGE_H
#define LIBRIPPLE_INCREMENTALUPDATEMESSAGE_H

#include "AbstractMessage.h"

namespace Ripple {
    namespace Common {
        namespace Entity {

            class IncrementalUpdateMessage final : public AbstractMessage {
            public:
                IncrementalUpdateMessage();

                IncrementalUpdateMessage(std::string applicationName, std::string key,
                                         uuid_t baseMessageUuid, std::string atomOperation, std::string value,
                                         time_t lastUpdate, int lastUpdateServerId);

                IncrementalUpdateMessage(uuid_t uuid, std::string applicationName, std::string key,
                                         uuid_t baseMessageUuid, std::string atomOperation, std::string value,
                                         time_t lastUpdate, int lastUpdateServerId);

                ~IncrementalUpdateMessage() final;

                IncrementalUpdateMessage(const IncrementalUpdateMessage &) = delete;

                IncrementalUpdateMessage &operator=(const IncrementalUpdateMessage &) = delete;

                const uuid_t &GetBaseMessageUuid() const;

                void SetBaseMessageUuid(uuid_t baseMessageUuid);

                const std::string &GetAtomicOperation() const;

                void SetAtomicOperation(std::string atomicOperation);

                const std::string &GetValue() const;

                void SetValue(std::string value);

            private:
                uuid_t baseMessageUuid;
                std::string atomicOperation;
                std::string value;

            };
        }
    }
}

#endif //LIBRIPPLE_INCREMENTALUPDATEMESSAGE_H
