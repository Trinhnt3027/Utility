#include "TimeHelper/DateTime.h"

using namespace Utility::TimeHelper;

class DateTime::DateTimeImpl
{
public:
    DateTimeImpl();
    DateTimeImpl(const DateTimeImpl& other);

    std::unique_ptr<DateTimeImpl> clone();

    friend class DateTime;
private:
    int m_year;
    int m_month;
    int m_day;
    int m_hour;
    int m_minute;
    int m_seccond;
    int m_milisec;
    long m_microsec;
};

DateTime::DateTimeImpl::DateTimeImpl()
    : m_year(-1)
    , m_month(-1)
    , m_day(-1)
    , m_hour(-1)
    , m_minute(-1)
    , m_seccond(-1)
    , m_milisec(-1)
    , m_microsec(-1)
{

}

DateTime::DateTimeImpl::DateTimeImpl(const DateTime::DateTimeImpl &other)
    : m_year(other.m_year)
    , m_month(other.m_month)
    , m_day(other.m_day)
    , m_hour(other.m_hour)
    , m_minute(other.m_minute)
    , m_seccond(other.m_seccond)
    , m_milisec(other.m_milisec)
    , m_microsec(other.m_microsec)
{

}

std::unique_ptr<DateTime::DateTimeImpl> DateTime::DateTimeImpl::clone()
{
    return std::make_unique<DateTime::DateTimeImpl>(*this);
}



DateTime::DateTime()
{
    mImplPtr = std::make_unique<DateTimeImpl>();
}

DateTime::DateTime(int year, int month, int day, int hour, int minute, int second, int milisec, long microsec)
    : DateTime()
{
    mImplPtr->m_year = year;
    mImplPtr->m_month = month;
    mImplPtr->m_day = day;
    mImplPtr->m_hour = hour;
    mImplPtr->m_minute = minute;
    mImplPtr->m_seccond = second;
    mImplPtr->m_milisec = milisec;
    mImplPtr->m_microsec = microsec;
}


DateTime::DateTime(const DateTime &other)
{
    mImplPtr = other.mImplPtr->clone();
}

DateTime::~DateTime()
{

}

int DateTime::year()
{
    return  mImplPtr->m_year;
}

int DateTime::month()
{
    return  mImplPtr->m_month;
}

int DateTime::day()
{
    return  mImplPtr->m_day;
}

int DateTime::hour()
{
    return  mImplPtr->m_hour;
}

int DateTime::minute()
{
    return  mImplPtr->m_minute;
}

int DateTime::second()
{
    return  mImplPtr->m_seccond;
}

int DateTime::milisec()
{
    return  mImplPtr->m_milisec;
}

long DateTime::microsec()
{
    return  mImplPtr->m_microsec;
}

std::string DateTime::toString(TimeFormat format, TimeExtension ext)
{
    char buff[50];

    switch (format) {
    case TimeFormat::yyyy_MM_dd:
        sprintf(buff, "%04d-%02d-%02d %02d:%02d:%02d", mImplPtr->m_year, mImplPtr->m_month, mImplPtr->m_day,
                mImplPtr->m_hour, mImplPtr->m_minute, mImplPtr->m_seccond);
        break;
    default:
        sprintf(buff, "%04d-%02d-%02d %02d:%02d:%02d", mImplPtr->m_year, mImplPtr->m_month, mImplPtr->m_day,
                mImplPtr->m_hour, mImplPtr->m_minute, mImplPtr->m_seccond);
        break;
    }
    std::string mainTime(buff);

    switch (ext) {
    case TimeExtension::NONE:
        buff[0] = '\0'; //for empty string
        break;
    case TimeExtension::MILI_SEC:
        sprintf(buff, ":%03d", mImplPtr->m_milisec);
        break;
    case TimeExtension::MICRO_SEC:
        sprintf(buff, ":%03ld", mImplPtr->m_microsec);
        break;
    default:
        buff[0] = '\0'; //for empty string
        break;
    }
    std::string extTime(buff);

    return mainTime + extTime;
}

DateTime DateTime::operator =(const DateTime &other)
{
    mImplPtr = other.mImplPtr->clone();
    return *this;
}
