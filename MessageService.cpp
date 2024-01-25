// Copyright (c) 2023 Institute of Software, Chinese Academy of Sciences
// libripple is licensed under Mulan PSL v2.
// You can use this software according to the terms and conditions of the Mulan PSL v2.
// You may obtain a copy of Mulan PSL v2 at:
//          http://license.coscl.org.cn/MulanPSL2
// THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
// EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
// MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
// See the Mulan PSL v2 for more details.

#include "MessageService.h"
#include <memory>

// TODO: Implement this
namespace Ripple {
    namespace Common {
        namespace Storage {
            MessageService::MessageService(Storage *storage) {
                this->storage = storage;
            }

            MessageService::~MessageService() {

            }

            bool MessageService::NewMessage(Entity::AbstractMessage message) {
                // TODO: Implement this
                return false;
            }

            bool MessageService::Exist(uuid_t messageUuid) {
                // TODO: Implement this
                return false;
            }

            bool MessageService::NewUpdateMessage(Entity::UpdateMessage updateMessage) {
                // TODO: Implement this
                return false;
            }

            bool MessageService::NewDeleteMessage(Entity::DeleteMessage deleteMessage) {
                // TODO: Implement this
                return false;
            }

            bool
            MessageService::NewIncrementalUpdateMessage(Entity::IncrementalUpdateMessage incrementalUpdateMessage) {
                // TODO: Implement this
                return false;
            }

            std::shared_ptr<Entity::AbstractMessage> MessageService::GetMessageByUuid(uuid_t messageUuid) {
                // TODO: Implement this
                return std::shared_ptr<Entity::AbstractMessage>();
            }

            std::vector<std::shared_ptr<Entity::AbstractMessage>>
            MessageService::FindMessages(const std::string& applicationName, const std::string& key) {
                // TODO: Implement this
                return std::vector<std::shared_ptr<Entity::AbstractMessage>>();
            }

            std::shared_ptr<Entity::AbstractMessage> MessageService::ParseMessage(sqlite3_stmt *statement) {
                // TODO: Implement this
                return std::shared_ptr<Entity::AbstractMessage>();
            }
        }
    }
}