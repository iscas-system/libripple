// Copyright (c) 2023 Institute of Software, Chinese Academy of Sciences
// libripple is licensed under Mulan PSL v2.
// You can use this software according to the terms and conditions of the Mulan PSL v2.
// You may obtain a copy of Mulan PSL v2 at:
//          http://license.coscl.org.cn/MulanPSL2
// THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
// EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
// MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
// See the Mulan PSL v2 for more details.

#include <cstdio>
#include <cstdarg>
#include <cstring>
#include "Logger.h"

#define LOG_LEVEL_INFO 1
#define LOG_LEVEL_ERROR 2

#define COLOR_NONE "\033[m"
#define COLOR_RED "\033[0;32;31m"
#define COLOR_BOLD_RED "\033[1;32;31m"
#define COLOR_YELLOW "\033[1;33m"

namespace Ripple {
    namespace Common {
        bool Logger::Enable = true;

        int Logger::LogLevel = LOG_LEVEL_INFO;

        Logger::Logger() {

        }

        Logger::~Logger() {

        }

        void Logger::Info(const char *source, const char *format, ...) {
            if (Logger::Enable && Logger::LogLevel <= LOG_LEVEL_INFO) {
                printf(COLOR_YELLOW "[%s] " COLOR_NONE, source);
                va_list arguments;
                va_start(arguments, format);
                vprintf(format, arguments);
                va_end(arguments);
                printf("\n");
            }
        }

        void Logger::Error(const char *source, const char *format, ...) {
            if (Logger::Enable && Logger::LogLevel <= LOG_LEVEL_ERROR) {
                printf(COLOR_YELLOW "[%s] " COLOR_NONE, source);
                printf(COLOR_BOLD_RED);
                va_list arguments;
                va_start(arguments, format);
                vprintf(format, arguments);
                va_end(arguments);
                printf("\n");
                printf(COLOR_NONE);
            }
        }

        void Logger::Error(int errorNumber, const char *source, const char *format, ...) {
            if (Logger::Enable && Logger::LogLevel <= LOG_LEVEL_ERROR) {
                printf(COLOR_YELLOW "[%s] " COLOR_NONE, source);
                printf(COLOR_BOLD_RED);
                va_list arguments;
                va_start(arguments, format);
                vprintf(format, arguments);
                va_end(arguments);
                printf(" (%s)\n", strerror(errorNumber));
                printf(COLOR_NONE);
            }
        }
    }
} // Ripple
