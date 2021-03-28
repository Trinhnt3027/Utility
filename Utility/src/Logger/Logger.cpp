#include <iostream>
#include <map>
#include <sstream>
#include <algorithm>
#include <mutex>
#include <fstream>

#include <boost/filesystem.hpp>

#ifdef _WIN32

#else
#include <unistd.h>
#include <sys/syscall.h>
#endif

#include "Logger/Logger.h"
#include "TimeHelper/TimeHelper.h"

using namespace Utility::Logger;
using namespace Utility::TimeHelper;

namespace fs = boost::filesystem;

class Logger::LoggerImlp {
public:
    LoggerImlp();

    void initialize(const std::string &appName, const std::list<LogOutput>& logOutput);
    void initialize(const std::string &appName, const std::string &logPath, const std::list<LogOutput>& logOutput);

    void writeLog(const LogType &type, const std::string &logData);

private:
    void initLogEnable();
    void initLogFile();

public:
    std::string m_appName;
    std::string m_logPath;

private:
    fs::path m_fsPath;
    std::string m_logFilePrefix;
    u_int8_t m_fileCout;
    std::list<LogOutput> m_logOutput;
    bool m_enableLogConsole;
    bool m_enableLogFile;
    bool m_enableLog;
    const std::map<LogType, std::string> m_LogName
    {
        {LogType::INFO,    "INF"},
        {LogType::DEBUG,   "DBG"},
        {LogType::WARNING, "WAR"},
        {LogType::ERROR,   "ERR"}
    };

    std::mutex m_mutex;

private:
    const uint16_t m_MaxFileSize = 5120;    // 5MB * 1024
    const u_int8_t m_maxFileCount = 5;
};

Logger::LoggerImlp::LoggerImlp()
    : m_appName("")
    , m_logPath("")
    , m_logFilePrefix("")
    , m_fileCout(0)
    , m_logOutput{}
    , m_enableLogConsole(false)
    , m_enableLogFile(false)
    , m_enableLog(false)
{

}

void Logger::LoggerImlp::initialize(const std::string &appName, const std::list<LogOutput> &logOutput)
{
    m_appName = appName;
    m_logOutput = logOutput;
    initLogEnable();
    initLogFile();
}

void Logger::LoggerImlp::initialize(const std::string &appName, const std::string &logPath, const std::list<LogOutput> &logOutput)
{
    m_logPath = logPath;
    initialize(appName, logOutput);
}

void Logger::LoggerImlp::writeLog(const LogType &type, const std::string &logData)
{
    if ((m_enableLog) && (m_appName.empty() == false)) {
        std::stringstream outLog;
        unsigned long pid;
        unsigned long tid;

#ifdef _WIN32

#else
        pid = syscall(__NR_getpid);
        tid = syscall(__NR_gettid);
#endif

        outLog << TimeHelper::TimeHelper::getInstance().getCurrentDateTime().toString(TimeFormat::yyyy_MM_dd, TimeExtension::MICRO_SEC)
               << " " << m_LogName.at(type) << " " << m_appName
               << " " << "[" << pid << ":" << tid << "]" << logData;
        std::string logData = outLog.str();

        // Enable console log
        if (m_enableLogConsole) {
            std::lock_guard<std::mutex> guard(m_mutex);

            std::cout << logData;
        }

        //Enable file log
        if (m_enableLogFile) {
            std::lock_guard<std::mutex> guard(m_mutex);

            if (fs::file_size(m_fsPath) > m_MaxFileSize) {
                if (m_fileCout == m_maxFileCount) {
                    //remove the first log file
                    fs::path previousLogFile = fs::path(m_logPath) / (m_logFilePrefix + "1.log");
                    fs::remove(previousLogFile);

                    //shift file
                    for (uint8_t i = 2; i <= m_fileCout; i++) {
                        fs::path nextLogFile = fs::path(m_logPath) / (m_logFilePrefix + std::to_string(i) + ".log");
                        fs::rename(nextLogFile, previousLogFile);
                        previousLogFile = nextLogFile;
                    }
                }
                else {
                    m_fileCout++;
                    m_fsPath = fs::path(m_logPath) / (m_logFilePrefix + std::to_string(m_fileCout) + ".log");
                }
            }

            std::ofstream outFile{m_fsPath.string().c_str(), std::ios::out | std::ios::app};
            outFile << logData;
            outFile.flush();
            outFile.close();
        }
    }
}

void Logger::LoggerImlp::initLogEnable()
{
    m_enableLogConsole = std::find(m_logOutput.begin(), m_logOutput.end(), LogOutput::CONSOLE) != m_logOutput.end();
    m_enableLogFile    = std::find(m_logOutput.begin(), m_logOutput.end(), LogOutput::FILE) != m_logOutput.end();

    m_enableLog = m_enableLogFile || m_enableLogConsole;
}

void Logger::LoggerImlp::initLogFile()
{
    if (m_logPath.empty()) {
        m_fsPath = fs::current_path();
        m_logPath = m_fsPath.string();
    }
    else {
        m_fsPath = fs::path(m_logPath);
    }

    if (fs::exists(m_fsPath) == false) {
        fs::create_directory(m_fsPath);
    }

    std::string m_logFilePrefix = m_appName;
    fs::path logFilePath = m_fsPath / (m_logFilePrefix + "1.log");
    if (fs::exists(logFilePath) == false) {
        m_fsPath = logFilePath;
        m_fileCout = 1;
        std::ofstream logFile{logFilePath.string().c_str(), std::ios::out};
        logFile.close();
    }
    else {
        int idx = 1;
        std::string logFileTmp = m_logFilePrefix;
        fs::path lastFilePath;
        do {
            idx++;
            lastFilePath = logFilePath;
            logFileTmp =m_logFilePrefix + std::to_string(idx);
            logFilePath = m_fsPath / (logFileTmp + ".log");
        } while (fs::exists(logFilePath));
        m_fsPath = lastFilePath;
        m_fileCout = idx - 1;
    }

}


/*******************************************/
Logger* Logger::mInstancePtr = nullptr;

Logger::Logger()
{
    mImplPtr = std::make_unique<LoggerImlp>();
}

Logger &Logger::getInstance()
{
    if (mInstancePtr == nullptr) {
        mInstancePtr = new Logger();
    }
    return *mInstancePtr;
}

void Logger::initialize(const std::string &appName, const std::list<LogOutput>& logOutput)
{
    mImplPtr->initialize(appName, logOutput);
}

void Logger::initialize(const std::string &appName, const std::string &logPath, const std::list<LogOutput>& logOutput)
{
    mImplPtr->initialize(appName, logPath, logOutput);
}

std::string Logger::getAppName() const
{
    return mImplPtr->m_appName;
}

std::string Logger::getLogPath() const
{
    return mImplPtr->m_logPath;
}

void Logger::writeLog(const LogType &type, const std::string &logData)
{
    mImplPtr->writeLog(type, logData);
}
