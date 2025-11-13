#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <string>
#include <fstream>
#include <mutex>
#include "types.hpp"

class Logger
{
public:
    static Logger &getInstance();

    void log(LogLevel level, const std::string &message);
    void setLogLevel(LogLevel level);
    void setLogFile(const std::string &filepath);

    // Delete copy constructor and assignment operator
    Logger(const Logger &) = delete;
    Logger &operator=(const Logger &) = delete;

private:
    Logger();
    ~Logger();

    LogLevel currentLevel_;
    std::ofstream logFile_;
    std::mutex mutex_;

    std::string levelToString(LogLevel level) const;
    std::string getCurrentTimestamp() const;
};

#endif // LOGGER_HPP
