#include <iostream>
#include <string>
#include <Utility/Logger/Logger.h>

using namespace Utility::Logger;

int main()
{
    Logger::getInstance().initialize("TEST", std::list<LogOutput>{LogOutput::FILE});
    LOG_INF() << "ascdcdc " << 123 << "xcddc";
    LOG_INF() << "efcdwd " << 342;
}
