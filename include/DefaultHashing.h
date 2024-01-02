// Copyright (c) 2023 Institute of Software, Chinese Academy of Sciences
// libripple is licensed under Mulan PSL v2.
// You can use this software according to the terms and conditions of the Mulan PSL v2.
// You may obtain a copy of Mulan PSL v2 at:
//          http://license.coscl.org.cn/MulanPSL2
// THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
// EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
// MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
// See the Mulan PSL v2 for more details.

#ifndef LIBRIPPLE_DEFAULTHASHING_H
#define LIBRIPPLE_DEFAULTHASHING_H

#include "Hashing.h"

namespace Ripple {
    namespace Common {
        namespace Hashing {
            class DefaultHashing final:public Hashing {
            public:
                DefaultHashing();

                ~DefaultHashing() override;

                DefaultHashing(const DefaultHashing &) = delete;

                DefaultHashing &operator=(const DefaultHashing &) = delete;

                std::vector<std::shared_ptr<Ripple::Common::Entity::NodeMetadata>>
                CalculateNodeList(std::string applicationName, std::string key,
                                  std::vector<std::shared_ptr<Ripple::Common::Entity::NodeMetadata>> nodeList) override;
            };
        }
    }
}

#endif //LIBRIPPLE_DEFAULTHASHING_H
