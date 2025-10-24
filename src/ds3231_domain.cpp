#include "ds3231_domain.h"
#include "ds3231_common.h"

namespace DS3231::domain
{
DateTimeFormatted DateTime::AsFormatted()
{
    std::string _hours = common::FormatDecWithLeadingZero(hours);
    if (is_meridial)
    {
        _hours += " " + is_am ? "am" : "pm";
    }
    return DateTimeFormatted{.seconds = common::FormatDecWithLeadingZero(seconds),
                             .minutes = common::FormatDecWithLeadingZero(minutes),
                             .hours = _hours,
                             .day = common::FormatDecWithLeadingZero(day),
                             .month = common::FormatDecWithLeadingZero(month),
                             .year = common::FormatDecWithLeadingZero(age) += common::FormatDecWithLeadingZero(year)};
}
} // namespace DS3231::domain