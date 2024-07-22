#pragma once

#include <format>
#include <fstream>

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

        void Log(LogLevel level, const char *position, const std::string &msg);

    private:
        std::ofstream _foutHandle;
        int _textColorMap[4];
        std::string _logLevelTextMap[4];
    };

    extern Logger gLogger;

} // namespace core

#define LOG_STATUS(...) core::gLogger.Log(core::LogLevel::STATUS, __FUNCTION__, std::format(__VA_ARGS__))
#define LOG_INFO(...) core::gLogger.Log(core::LogLevel::INFO, __FUNCTION__, std::format(__VA_ARGS__))
#define LOG_WARNING(...) core::gLogger.Log(core::LogLevel::WARN, __FUNCTION__, std::format(__VA_ARGS__))
#define LOG_ERROR(...) core::gLogger.Log(core::LogLevel::ERR, __FUNCTION__, std::format(__VA_ARGS__))
