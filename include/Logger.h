// Author: Zhen Tang <tangzhen12@otcaix.iscas.ac.cn>
// Affiliation: Institute of Software, Chinese Academy of Sciences

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
