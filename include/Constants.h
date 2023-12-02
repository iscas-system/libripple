// Copyright (c) 2023 Institute of Software, Chinese Academy of Sciences
// libripple is licensed under Mulan PSL v2.
// You can use this software according to the terms and conditions of the Mulan PSL v2.
// You may obtain a copy of Mulan PSL v2 at:
//          http://license.coscl.org.cn/MulanPSL2
// THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
// EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
// MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
// See the Mulan PSL v2 for more details.

#ifndef LIBRIPPLE_CONSTANTS_H
#define LIBRIPPLE_CONSTANTS_H

#include <string>

namespace Ripple {
    namespace Common {
        namespace Entity {
            class Constants final {
            public:
                Constants(const Constants &) = delete;

                Constants &operator=(const Constants &) = delete;

                ~Constants() = default;

                static constexpr const char *MESSAGE_TYPE_UPDATE = "update";
                static constexpr const char *MESSAGE_TYPE_DELETE = "delete";
                static constexpr const char *MESSAGE_TYPE_INCREMENTAL_UPDATE = "incremental_update";
                static constexpr const char *ATOMIC_OPERATION_ADD_ENTRY = "add_entry";
                static constexpr const char *ATOMIC_OPERATION_REMOVE_ENTRY = "remove_entry";

            private:
                Constants() = default;
            };
        }
    }
}

#endif //LIBRIPPLE_CONSTANTS_H
