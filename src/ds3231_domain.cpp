#include "ds3231_domain.h"
#include "ds3231_common.h"

namespace DS3231::domain
{
DateTimeFormatted DateTime::AsFormatted()
{
    return DateTimeFormatted{.seconds = common::FormatDecWithLeadingZero(seconds),
                             .minutes = common::FormatDecWithLeadingZero(minutes),
                             .hours = common::FormatDecWithLeadingZero(hours),
                             .day = common::FormatDecWithLeadingZero(day),
                             .month = common::FormatDecWithLeadingZero(month),
                             .year = common::FormatDecWithLeadingZero(age) += common::FormatDecWithLeadingZero(year)};
}
} // namespace DS3231::domain