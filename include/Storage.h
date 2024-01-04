// You can use this software according to the terms and conditions of the Mulan PSL v2.
// You may obtain a copy of Mulan PSL v2 at:
//          http://license.coscl.org.cn/MulanPSL2
// THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
// EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
// MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
// See the Mulan PSL v2 for more details.

#ifndef LIBRIPPLE_STORAGE_H
#define LIBRIPPLE_STORAGE_H

#include <string>
#include <sqlite3.h>
#include <memory>
#include "ItemService.h"
#include "MessageService.h"
#include "AckService.h"

// TODO: Implement this
namespace Ripple {
    namespace Common {
        namespace Storage {
            class Storage {
            public:
                Storage(std::string fileName);

                virtual ~Storage();

                Storage(const Storage &) = delete;

                Storage &operator=(const Storage &) = delete;

                const std::string &GetFileName() const;

            private:
                std::string fileName;
                sqlite3 *database;
                std::unique_ptr<ItemService> itemService;
                std::unique_ptr<MessageService> messageService;
                std::unique_ptr<AckService> ackService;

                void Initialize();

                void InitializeTables();

                void DoExecuteStatement(const char * statement);

                void SetFileName(std::string fileName);

            };
        }
    }
}

#endif //LIBRIPPLE_STORAGE_H
