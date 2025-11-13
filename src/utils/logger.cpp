#include "utils/logger.hpp"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <ctime>

Logger &Logger::getInstance()
{
    static Logger instance;
    return instance;
}

Logger::Logger() : currentLevel_(LogLevel::INFO)
{
}

Logger::~Logger()
{
    if (logFile_.is_open())
    {
        logFile_.close();
    }
}

void Logger::log(LogLevel level, const std::string &message)
{
    if (level < currentLevel_)
    {
        return;
    }

    std::lock_guard<std::mutex> lock(mutex_);

    std::string timestamp = getCurrentTimestamp();
    std::string levelStr = levelToString(level);
    std::string logMessage = "[" + timestamp + "] [" + levelStr + "] " + message;

    // Write to console
    std::cout << logMessage << std::endl;

    // Write to file if open
    if (logFile_.is_open())
    {
        logFile_ << logMessage << std::endl;
        logFile_.flush();
    }
}

void Logger::setLogLevel(LogLevel level)
{
    currentLevel_ = level;
}

void Logger::setLogFile(const std::string &filepath)
{
    std::lock_guard<std::mutex> lock(mutex_);

    if (logFile_.is_open())
    {
        logFile_.close();
    }

    logFile_.open(filepath, std::ios::app);
}

std::string Logger::levelToString(LogLevel level) const
{
    switch (level)
    {
    case LogLevel::DEBUG:
        return "DEBUG";
    case LogLevel::INFO:
        return "INFO";
    case LogLevel::WARNING:
        return "WARN";
    case LogLevel::ERROR:
        return "ERROR";
    default:
        return "UNKNOWN";
    }
}

std::string Logger::getCurrentTimestamp() const
{
    auto now = std::time(nullptr);
    auto tm = *std::localtime(&now);

    std::ostringstream oss;
    oss << std::put_time(&tm, "%Y-%m-%d %H:%M:%S");
    return oss.str();
}
