// Copyright (c) 2023 Institute of Software, Chinese Academy of Sciences
// libripple is licensed under Mulan PSL v2.
// You can use this software according to the terms and conditions of the Mulan PSL v2.
// You may obtain a copy of Mulan PSL v2 at:
//          http://license.coscl.org.cn/MulanPSL2
// THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
// EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
// MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
// See the Mulan PSL v2 for more details.

#ifndef LIBRIPPLE_ITEM_H
#define LIBRIPPLE_ITEM_H

#include <string>

namespace Ripple {
    namespace Common {
        namespace Entity {
            class Item {
            public:
                Item();

                Item(std::string applicationName, std::string key);

                virtual ~Item();

                Item(const Item &) = delete;

                Item &operator=(const Item &) = delete;

                bool operator==(const Item &item);

                const std::string &GetApplicationName() const;

                void SetApplicationName(std::string applicationName);

                const std::string &GetKey() const;

                void SetKey(std::string key);

            private:
                std::string applicationName;
                std::string key;
            };
        }
    }
}


#endif //LIBRIPPLE_ITEM_H
