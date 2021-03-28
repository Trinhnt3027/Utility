#pragma once

#include <string>
#include <memory>
#include "LibraryExportDefine.h"
#include "DateTimeType.h"
#include "DateTime.h"

namespace Utility {
namespace TimeHelper {
class UTILITY_API TimeHelper
{
private:
    TimeHelper();

public:
    static TimeHelper& getInstance();

    DateTime getCurrentDateTime();

private:
    static TimeHelper* mInstancePtr;
};
} // namespace TimeHelper
} // namespace Utility
