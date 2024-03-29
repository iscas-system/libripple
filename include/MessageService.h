// You can use this software according to the terms and conditions of the Mulan PSL v2.
// You may obtain a copy of Mulan PSL v2 at:
//          http://license.coscl.org.cn/MulanPSL2
// THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
// EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
// MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
// See the Mulan PSL v2 for more details.

#ifndef LIBRIPPLE_MESSAGESERVICE_H
#define LIBRIPPLE_MESSAGESERVICE_H

#include <uuid/uuid.h>
#include <memory>
#include <sqlite3.h>
#include "Storage.h"
#include "AbstractMessage.h"
#include "UpdateMessage.h"
#include "DeleteMessage.h"
#include "IncrementalUpdateMessage.h"

namespace Ripple {
    namespace Common {
        namespace Storage {
            class Storage;

            class MessageService {
            public:
                explicit MessageService(Storage *storage);

                virtual ~MessageService();

                MessageService(const MessageService &) = delete;

                MessageService &operator=(const MessageService &) = delete;

                bool NewMessage(const std::shared_ptr<Entity::AbstractMessage>& message);

                bool Exist(const uuid_t messageUuid);

                std::shared_ptr<Entity::AbstractMessage> GetMessageByUuid(uuid_t messageUuid);

                std::vector<std::shared_ptr<Entity::AbstractMessage>>
                FindMessages(const std::string &applicationName, const std::string &key);

            private:
                Storage *storage;
                std::mutex mutex;

                bool NewUpdateMessage(const std::shared_ptr<Entity::UpdateMessage>& updateMessage);

                bool NewDeleteMessage(const std::shared_ptr<Entity::DeleteMessage>& deleteMessage);

                bool NewIncrementalUpdateMessage(const std::shared_ptr<Entity::IncrementalUpdateMessage>& incrementalUpdateMessage);

                std::shared_ptr<Entity::AbstractMessage> ParseMessage(sqlite3_stmt *statement);

                void DoParseAbstractMessage(sqlite3_stmt *statement, std::shared_ptr<Entity::AbstractMessage> &message,
                                            std::string &messageType) const;
            };
        }
    }
}

#endif //LIBRIPPLE_MESSAGESERVICE_H
