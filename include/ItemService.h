// You can use this software according to the terms and conditions of the Mulan PSL v2.
// You may obtain a copy of Mulan PSL v2 at:
//          http://license.coscl.org.cn/MulanPSL2
// THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
// EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
// MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
// See the Mulan PSL v2 for more details.

#ifndef LIBRIPPLE_ITEMSERVICE_H
#define LIBRIPPLE_ITEMSERVICE_H

#include <vector>
#include <memory>
#include "Storage.h"
#include "Item.h"

// TODO: Implement this
namespace Ripple {
    namespace Common {
        namespace Storage {
            class Storage;

            class ItemService {
            public:
                explicit ItemService(Storage *storage);

                virtual ~ItemService();

                ItemService(const ItemService &) = delete;

                ItemService &operator=(const ItemService &) = delete;

                std::shared_ptr<Entity::Item> GetItem(std::string applicationName, std::string key);

            private:
                Storage *storage;
            };
        }
    }
}

#endif //LIBRIPPLE_ITEMSERVICE_H
