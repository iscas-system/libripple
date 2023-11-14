// Copyright (c) 2023 Institute of Software, Chinese Academy of Sciences
// libripple is licensed under Mulan PSL v2.
// You can use this software according to the terms and conditions of the Mulan PSL v2.
// You may obtain a copy of Mulan PSL v2 at:
//          http://license.coscl.org.cn/MulanPSL2
// THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
// EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
// MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
// See the Mulan PSL v2 for more details.

#ifndef LIBRIPPLE_LOGGER_H
#define LIBRIPPLE_LOGGER_H

namespace Ripple {

    class Logger {
    public:
        Logger(const Logger &) = delete;

        Logger &operator=(const Logger &) = delete;

        static void Info(const char *source, const char *format, ...);

        static void Error(int errorNumber, const char *source, const char *format, ...);

        static bool Enable;
        static int LogLevel;
    private:
        Logger();

        virtual ~Logger();
    };

} // Ripple

#endif //LIBRIPPLE_LOGGER_H
