#pragma once

namespace Utility {
namespace TimeHelper {

enum TimeInfo {
    YEAR = 0,
    MONTH,
    DAY,
    HOUR,
    MINUTE,
    SECOND,
    MILISEC,
    MICROSECS
};

enum TimeExtension {
    NONE = 0,
    MILI_SEC,
    MICRO_SEC,
};

enum TimeFormat {
    yyyy_MM_dd = 0,
};
} // namespace TimeHelper
} // namespace Utility
