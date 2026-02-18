#pragma once
#include "pico/stdlib.h"
#include <cstdint>
#include <string>

namespace DS3231::domain
{

struct IDateTimeBase
{
    uint8_t minutes = 0;
    uint8_t is_meridial = 0;
    uint8_t is_pm = 0;
    uint8_t hours = 0;
    uint8_t dow = 0;
    uint8_t day = 0;
};

struct IAlarmBase
{
    uint8_t minutes_off = 1;
    uint8_t hours_off = 1;
    uint8_t dow_off = 1;
    uint8_t day_off = 1;
    uint8_t day_is_dow = 0;
};

struct IAlarm2 : public IDateTimeBase, public IAlarmBase
{
};

struct IDateTimeExt : public IDateTimeBase
{
    uint8_t seconds = 0;
};

struct IAlarm1 : public IDateTimeExt, public IAlarmBase
{
    uint8_t seconds_off = 1;
};

struct IDateTimeFormatted
{
    std::string seconds;
    std::string minutes;
    std::string hours;
    std::string day;
    std::string month;
    std::string year;
};

struct IDateTimeDetailed : public IDateTimeExt
{
    uint8_t month = 0;
    uint8_t year = 0;
    uint8_t age = 0;
    IDateTimeFormatted AsFormatted();
};

struct Controls
{
    uint8_t EOSC = 0;  // работа генератора от батареи. Установка - 0, Сброс - 1
    uint8_t BBSQW = 0; // работа вывода INT/SQW в режиме SQW от батареи 1 - вкл, 0 - выкл
    uint8_t CONV = 0;  // преобразование температуры.
    uint8_t RS1 = 0;   // частота меандра на выход SQW
    uint8_t RS2 = 0;
    uint8_t INTCN = 0; // вывод INT/SQW 1 - прерывания будильника, 0 - меандр
    uint8_t A1IE = 0;  // Разрешает прерывание будильника 1. 1 - вкл 0 - выкл
    uint8_t A2IE = 0;  // Разрешает прерывание будильника 2. 1 - вкл 0 - выкл
};
} // namespace DS3231::domain