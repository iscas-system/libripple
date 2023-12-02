// Copyright (c) 2023 Institute of Software, Chinese Academy of Sciences
// libripple is licensed under Mulan PSL v2.
// You can use this software according to the terms and conditions of the Mulan PSL v2.
// You may obtain a copy of Mulan PSL v2 at:
//          http://license.coscl.org.cn/MulanPSL2
// THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
// EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
// MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
// See the Mulan PSL v2 for more details.

#ifndef LIBRIPPLE_ABSTRACTMESSAGE_H
#define LIBRIPPLE_ABSTRACTMESSAGE_H

#include <uuid/uuid.h>
#include <ctime>
#include <string>

namespace Ripple {
    namespace Common {
        namespace Entity {

            class AbstractMessage {
            public:
                AbstractMessage();

                AbstractMessage(uuid_t uuid, std::string type, std::string applicationName, std::string key,
                                time_t lastUpdate, int lastUpdateServerId);
                
                virtual ~AbstractMessage();

                AbstractMessage(const AbstractMessage &) = delete;

                AbstractMessage &operator=(const AbstractMessage &) = delete;

                const uuid_t &GetUuid() const;

                void SetUuid(uuid_t uuid);

                const std::string &GetType() const;

                void SetType(std::string type);

                const std::string &GetApplicationName() const;

                void SetApplicationName(std::string applicationName);

                const std::string &GetKey() const;

                void SetKey(std::string key);

                time_t GetLastUpdate() const;

                void SetLastUpdate(time_t lastUpdate);

                int GetLastUpdateServerId() const;

                void SetLastUpdateServerId(int lastUpdateServerId);

            private:
                uuid_t uuid;
                std::string type;
                std::string applicationName;
                std::string key;
                time_t lastUpdate;
                int lastUpdateServerId;
            };
        }
    }
} // Ripple

#endif //LIBRIPPLE_ABSTRACTMESSAGE_H
