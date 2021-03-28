#include <sstream>
#include "Logger/StreamLogger.h"

using namespace Utility::Logger;

StreamLogger::StreamLogger(std::function<void(const std::string& logData)> writer)
    : mWriter(writer)
{

}

StreamLogger::~StreamLogger()
{
    mStream << "\n";
    mWriter(mStream.str());
}
