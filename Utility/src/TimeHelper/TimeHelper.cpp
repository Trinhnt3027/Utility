#include <chrono>
#include "TimeHelper/TimeHelper.h"

using namespace Utility::TimeHelper;
using namespace std::chrono;

TimeHelper* TimeHelper::mInstancePtr = nullptr;

TimeHelper::TimeHelper()
{
}

TimeHelper &TimeHelper::getInstance()
{
    if (mInstancePtr == nullptr) {
        mInstancePtr = new TimeHelper();
    }
    return  *mInstancePtr;
}

DateTime TimeHelper::getCurrentDateTime()
{
    auto now = std::chrono::high_resolution_clock::now();
    auto seconds = std::chrono::time_point_cast<std::chrono::seconds>(now);
    auto fraction = now - seconds;
    auto microseconds = std::chrono::duration_cast<std::chrono::microseconds>(fraction);

    time_t tnow = std::chrono::high_resolution_clock::to_time_t(now);
    tm* ptm = localtime(&tnow);

    int year = ptm->tm_year + 1900;
    int month = ptm->tm_mon + 1;
    int day = ptm->tm_mday;
    int hour = ptm->tm_hour;
    int minute = ptm->tm_min;
    int second = ptm->tm_sec;
    long microsec = static_cast<int>(microseconds.count());
    int milisec = microsec / 1000;

    return DateTime(year, month, day, hour, minute, second, milisec, microsec);
}
