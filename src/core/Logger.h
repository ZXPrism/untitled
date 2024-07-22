#pragma once

#include <fstream>
#include <sstream>

namespace core {

    enum class LogLevel
    {
        STATUS,
        INFO,
        WARN,
        ERR
    };

    class Logger
    {
    public:
        Logger();
        ~Logger();

        void Log(LogLevel level, const char *position, const char *fmt, ...);

    private:
        void _PrintTime();

    private:
        std::ofstream _foutHandle;
        std::stringstream _logBuffer;
    };

    extern Logger gLogger;

} // namespace core

#define LOG_STATUS(...) core::gLogger.Log(core::LogLevel::STATUS, __FUNCTION__, __VA_ARGS__)
#define LOG_INFO(...) core::gLogger.Log(core::LogLevel::INFO, __FUNCTION__, __VA_ARGS__)
#define LOG_WARNING(...) core::gLogger.Log(core::LogLevel::WARN, __FUNCTION__, __VA_ARGS__)
#define LOG_ERROR(...) core::gLogger.Log(core::LogLevel::ERR, __FUNCTION__, __VA_ARGS__)
