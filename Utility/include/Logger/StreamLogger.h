#pragma once

#include <functional>
#include <string>
#include <memory>
#include <sstream>

namespace Utility {
namespace Logger {
class StreamLogger
{
public:
    StreamLogger(std::function<void(const std::string& logData)> writer);
    ~StreamLogger();

    template<typename T>
    StreamLogger& operator << (T t) {
        mStream << t;
        return *this;
    }

private:
    std::function<void(const std::string& logData)> mWriter;
    std::stringstream mStream;
};
} // namespace Logger
} // namespace Utility
