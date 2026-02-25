#pragma once
#include "pico/stdlib.h"
#include <cstdint>
#include <string>

namespace DS3231::domain
{

struct IHourData
{
    uint8_t is_meridial = 0;
    uint8_t is_pm = 0;
    uint8_t hours = 0;
};

struct IDateTimeBase : public IHourData
{
    IDateTimeBase(uint8_t minutes_, uint8_t is_meridial_, uint8_t is_pm_, uint8_t hours_, uint8_t day_, uint8_t dow_,
                  uint8_t day_is_dow_)
        : IHourData(is_meridial_, is_pm_, hours_), minutes(minutes_), day_is_dow(day_is_dow_), day(day_), dow(dow_)
    {
    }
    uint8_t minutes = 0;
    uint8_t day_is_dow = 0;
    uint8_t day = 0;
    uint8_t dow = 0;
};

struct IAlarmBase
{
    uint8_t minutes_off = 1;
    uint8_t hours_off = 1;
    uint8_t day_off = 1;
};

struct IAlarm2 : public IDateTimeBase, public IAlarmBase
{
    IAlarm2(uint8_t minutes_ = 0, uint8_t is_meridial_ = 0, uint8_t is_pm_ = 0, uint8_t hours_ = 0, uint8_t day_ = 0,
            uint8_t dow_ = 0, uint8_t day_is_dow_ = 0, uint8_t minutes_off_ = 0, uint8_t hours_off_ = 0,
            uint8_t day_off_ = 0)
        : IDateTimeBase(minutes_, is_meridial_, is_pm_, hours_, day_, dow_, day_is_dow_),
          IAlarmBase(minutes_off_, hours_off_, day_off_)
    {
    }
};

struct IDateTimeExt : public IDateTimeBase
{
    uint8_t seconds = 0;
    IDateTimeExt(uint8_t seconds_ = 0, uint8_t minutes_ = 0, uint8_t is_meridial_ = 0, uint8_t is_pm_ = 0,
                 uint8_t hours_ = 0, uint8_t day_ = 0, uint8_t dow_ = 0, uint8_t day_is_dow_ = 0)
        : IDateTimeBase(minutes_, is_meridial_, is_pm_, hours_, day_, dow_, day_is_dow_), seconds(seconds_)
    {
    }
};

struct IAlarm1 : public IDateTimeExt, public IAlarmBase
{
    uint8_t seconds_off = 1;
    IAlarm1(uint8_t seconds_ = 0, uint8_t minutes_ = 0, uint8_t is_meridial_ = 0, uint8_t is_pm_ = 0,
            uint8_t hours_ = 0, uint8_t day_ = 0, uint8_t dow_ = 0, uint8_t day_is_dow_ = 0, uint8_t seconds_off_ = 0,
            uint8_t minutes_off_ = 0, uint8_t hours_off_ = 0, uint8_t day_off_ = 0)
        : IDateTimeExt(seconds_, minutes_, is_meridial_, is_pm_, hours_, day_, dow_, day_is_dow_),
          IAlarmBase(minutes_off_, hours_off_, day_off_), seconds_off(seconds_off_)
    {
    }
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
    uint8_t age = 20;

    IDateTimeDetailed(uint8_t seconds_ = 0, uint8_t minutes_ = 0, uint8_t is_meridial_ = 0, uint8_t is_pm_ = 0,
                      uint8_t hours_ = 0, uint8_t day_ = 0, uint8_t dow_ = 0, uint8_t day_is_dow_ = 0,
                      uint8_t month_ = 0, uint8_t year_ = 0, uint8_t age_ = 20)
        : IDateTimeExt(seconds_, minutes_, is_meridial_, is_pm_, hours_, day_, dow_, day_is_dow_), month(month_),
          year(year_), age(age_)
    {
    }

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

struct State
{
    uint8_t OSF = 0;
    uint8_t EN32 = 0;
    uint8_t BSY = 0;
    uint8_t A2F = 0;
    uint8_t A1F = 0;
};
} // namespace DS3231::domain