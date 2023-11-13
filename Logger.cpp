// Author: Zhen Tang <tangzhen12@otcaix.iscas.ac.cn>
// Affiliation: Institute of Software, Chinese Academy of Sciences

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
} // Ripple
