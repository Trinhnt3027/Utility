#pragma once

#include <memory>
#include <string>
#include "LibraryExportDefine.h"
#include "DateTimeType.h"

namespace Utility {
namespace TimeHelper {
class UTILITY_API DateTime
{
public:
    DateTime();
    DateTime(int year, int month, int day, int hour, int minute, int second = 0, int milisec = 0, long microsec = 0);
    DateTime(const std::string& timeStr) = delete;
    DateTime(const DateTime& other);

    ~DateTime();

    int year();
    int month();
    int day();
    int hour();
    int minute();
    int second();
    int milisec();
    long microsec();

    std::string toString(TimeFormat format = TimeFormat::yyyy_MM_dd, TimeExtension ext = TimeExtension::NONE);

    DateTime operator = (const DateTime& other);

private:
    class DateTimeImpl;
    std::unique_ptr<DateTimeImpl> mImplPtr;

};
} // namespace TimeHelper
} // namespace Utility
