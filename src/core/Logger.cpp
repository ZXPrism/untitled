#include "Logger.h"

#include "Console.h"
#include "Settings.h"

#include <chrono>
#include <format>
#include <iostream>

namespace core {

    Logger gLogger;

    Logger::Logger()
    {
        _foutHandle.open(LOG_FILE_PATH);

        if (!_foutHandle)
        {
            std::cout << "fatal: could not open logger file handle!" << std::endl;
            return;
        }

        _textColorMap[(int)LogLevel::STATUS] = 10;
        _textColorMap[(int)LogLevel::INFO] = 11;
        _textColorMap[(int)LogLevel::WARN] = 14;
        _textColorMap[(int)LogLevel::ERR] = 12;

        _logLevelTextMap[(int)LogLevel::STATUS] = "STATUS";
        _logLevelTextMap[(int)LogLevel::INFO] = "INFO";
        _logLevelTextMap[(int)LogLevel::WARN] = "WARN";
        _logLevelTextMap[(int)LogLevel::ERR] = "ERR";

        LOG_STATUS("Successfully launched logger!");
    }

    Logger::~Logger()
    {
        if (_foutHandle.is_open())
        {
            _foutHandle.close();
        }
    }

    void Logger::Log(LogLevel level, const char *position, const std::string &msg)
    {
        std::string logMsg;
        auto now = std::chrono::system_clock::now();
        auto tt = std::chrono::system_clock::to_time_t(now);
        auto pTime = std::localtime(&tt);

        logMsg = std::format("[{} / {:0>2}:{:0>2}:{:0>2}] <{}> {}", _logLevelTextMap[(int)level],
                             pTime->tm_hour, pTime->tm_min, pTime->tm_sec, position, msg);
        gConsole.SetTextColor(_textColorMap[(int)level]);
        std::cout << logMsg << std::flush;
        _foutHandle << logMsg << std::flush;
    }

} // namespace core
