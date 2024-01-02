// You can use this software according to the terms and conditions of the Mulan PSL v2.
// You may obtain a copy of Mulan PSL v2 at:
//          http://license.coscl.org.cn/MulanPSL2
// THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
// EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
// MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
// See the Mulan PSL v2 for more details.

#ifndef LIBRIPPLE_MESSAGESERVICE_H
#define LIBRIPPLE_MESSAGESERVICE_H

// TODO: Implement this
namespace Ripple {
    namespace Common {
        namespace Storage {
            class MessageService {
            public:
                MessageService();

                virtual ~MessageService();

                MessageService(const MessageService &) = delete;

                MessageService &operator=(const MessageService &) = delete;
            };
        }
    }
}

#endif //LIBRIPPLE_MESSAGESERVICE_H
