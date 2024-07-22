#include "Logger.h"

#include "Console.h"
#include "Settings.h"

#include <chrono>
#include <cstdarg>
#include <iomanip>
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

        _logBuffer.fill('0');

        LOG_STATUS("Successfully launched logger!");
    }

    Logger::~Logger()
    {
        if (_foutHandle.is_open())
        {
            _foutHandle.close();
        }
    }

    void Logger::Log(LogLevel level, const char *position, const char *fmt, ...)
    {
        static char buffer[4096];

        _logBuffer.str("");

        switch (level)
        {
        case LogLevel::STATUS:
            gConsole.SetTextColor(10);
            _logBuffer << "[STATUS / ";
            break;
        case LogLevel::INFO:
            gConsole.SetTextColor(11);
            _logBuffer << "[INFO / ";
            break;
        case LogLevel::WARN:
            gConsole.SetTextColor(14);
            _logBuffer << "[WARNING / ";
            break;
        case LogLevel::ERR:
            gConsole.SetTextColor(12);
            _logBuffer << "[ERROR / ";
            break;
        default:
            break;
        }

        _PrintTime();

        _logBuffer << "] <" << position << "> ";

        std::va_list args;
        va_start(args, fmt);
        std::vsprintf(buffer, fmt, args);
        va_end(args);
        _logBuffer << buffer << '\n';

        std::string logMsg = _logBuffer.str();
        std::cout << logMsg << std::flush;
        _foutHandle << logMsg << std::flush;
    }

    void Logger::_PrintTime()
    {
        auto now = std::chrono::system_clock::now();
        auto tt = std::chrono::system_clock::to_time_t(now);
        auto pTime = std::localtime(&tt);

        _logBuffer << std::setw(2) << pTime->tm_hour << ':' << std::setw(2) << pTime->tm_min << ':'
                   << std::setw(2) << pTime->tm_sec;
    }

} // namespace core
