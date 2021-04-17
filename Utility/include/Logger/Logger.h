#pragma once

#include <string>
#include <memory>
#include "StreamLogger.h"
#include <list>

namespace Utility {
namespace Logger {

enum LogType {
    INFO = 0,
    DEBUG,
    WARNING,
    ERROR
};

enum LogOutput {
    CONSOLE = 0,
    FILE,
};

#define LOG_INF() StreamLogger([] (const std::string& logData) { \
    Logger::getInstance().writeLog(LogType::INFO, logData); \
})

#define LOG_DBG() StreamLogger([] (const std::string& logData) { \
    Logger::getInstance().writeLog(LogType::DEBUG, logData); \
})

#define LOG_WAR() StreamLogger([] (const std::string& logData) { \
    Logger::getInstance().writeLog(LogType::WARNING, logData); \
})

#define LOG_ERR() StreamLogger([] (const std::string& logData) { \
    Logger::getInstance().writeLog(LogType::ERROR, logData); \
})

class Logger
{
private:
    Logger();

public:
    static Logger& getInstance();
    void initialize(const std::string& appName, const std::list<LogOutput>& logOutput);
    void initialize(const std::string& appName, const std::string& logPath,  const std::list<LogOutput>& logOutput);

    std::string getAppName() const;
    std::string getLogPath() const;

    void writeLog(const LogType& type, const std::string& logData);

private:
    class LoggerImlp;
    std::unique_ptr<LoggerImlp> mImplPtr;

    static Logger* mInstancePtr;
};
} // namespace Logger
} // namespace Utility
