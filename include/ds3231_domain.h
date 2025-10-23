#pragma once
#include "pico/stdlib.h"
#include <cstdint>
#include <string>

namespace DS3231::domain
{
struct DateTimeFormatted
{
    std::string seconds;
    std::string minutes;
    std::string hours;
    std::string day;
    std::string month;
    std::string year;
};

struct DateTime
{
    uint8_t seconds = 0;
    uint8_t minutes = 0;
    uint8_t hours = 0;
    uint8_t dow = 0;
    uint8_t day = 0;
    uint8_t month = 0;
    uint8_t year = 0;
    bool is_meridial = false;
    bool is_am = false;
    uint16_t age = 20;

    DateTimeFormatted AsFormatted();
};
}; // namespace DS3231::domain