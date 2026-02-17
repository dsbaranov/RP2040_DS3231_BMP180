#include "ds3231_domain.h"
#include "ds3231_common.h"

namespace DS3231::domain
{

IDateTimeFormatted IDateTimeDetailed::AsFormatted()
{
    std::string _hours = common::FormatDecWithLeadingZero(hours);
    if (is_meridial)
    {
        _hours += is_pm ? "pm" : "am";
    }
    return IDateTimeFormatted{common::FormatDecWithLeadingZero(seconds),
                              common::FormatDecWithLeadingZero(minutes),
                              _hours,
                              common::FormatDecWithLeadingZero(day),
                              common::FormatDecWithLeadingZero(month),
                              common::FormatDecWithLeadingZero(age) += common::FormatDecWithLeadingZero(year)};
    return IDateTimeFormatted();
}
} // namespace DS3231::domain