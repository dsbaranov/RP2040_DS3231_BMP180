#pragma once
#include "ds3231_domain.h"
#include "ds3231_registers.h"
#include "i2c/i2c_device.h"
#include <algorithm>

namespace DS3231
{
using namespace REGISTERS;

class DS3231 : public I2CDevice
{
  public:
    DS3231(i2c_inst_t *i2c);
    DS3231() = delete;
    DS3231(const DS3231 &) = delete;
    DS3231(DS3231 &&) = delete;

    void init();

    uint8_t GetSeconds();
    uint8_t GetMinutes();
    uint8_t GetHours();
    uint8_t GetDow();
    uint8_t GetDay();
    uint8_t GetMonth();
    uint8_t GetAge();
    uint8_t GetYear();
    std::string GetFormattedSeconds();
    std::string GetFormattedMinutes();
    std::string GetFormattedHours();
    std::string GetFormattedDay();
    std::string GetFormattedMonth();
    std::string GetFormattedYear();

    DS3231 &SetSeconds(uint8_t value = 0);
    DS3231 &SetMinutes(uint8_t value = 0);
    DS3231 &SetHours(uint8_t value = 0, uint8_t is_meridial = 0, uint8_t is_am = 0);
    DS3231 &SetDow(uint8_t value);
    DS3231 &SetDay(uint8_t value);
    DS3231 &SetMonth(uint8_t value);
    DS3231 &SetYear(uint16_t value);

    template <typename T> DS3231 &SetAlarm(T &&interface)
    {
        set_alarm(std::forward<T>(interface));
        return *this;
    }

    void SetDateTimeBlock(const domain::IDateTimeDetailed &datetime);

    domain::IDateTimeDetailed GetDateTime();
    const domain::IDateTimeDetailed &GetDateTimeConst();

    void ReadControls();
    DS3231 &SetControls();

    const std::vector<uint8_t> &getBuffer()
    {
        return data_buffer_;
    }

  private:
    domain::IDateTimeDetailed datetime_;
    domain::Controls controls;

    void read_bulk_date_time_block();

    static uint8_t decode_seconds(uint8_t seconds);
    static uint8_t decode_minutes(uint8_t minutes);
    uint8_t decode_hours(uint8_t hours);
    static uint8_t decode_dow(uint8_t dow);
    static uint8_t decode_day(uint8_t day);
    uint8_t decode_month(uint8_t month);
    static uint8_t decode_year(uint8_t year);
    static uint8_t encode_seconds(uint8_t seconds);
    static uint8_t encode_minutes(uint8_t minutes);
    static uint8_t encode_hours(uint8_t hours, uint8_t is_meridial, uint8_t is_pm);
    static uint8_t encode_dow(uint8_t dow);
    static uint8_t encode_day(uint8_t day);
    static uint8_t encode_month(uint8_t month);
    static uint8_t encode_year(uint8_t year);

    void set_alarm(const domain::IAlarm1 &);
    void set_alarm(domain::IAlarm1 &&);
    void set_alarm(const domain::IAlarm2 &);
    void set_alarm(domain::IAlarm2 &&);

    void read_seconds_register();
    void read_minutes_register();
    void read_hours_register();
    void read_dow_register();
    void read_day_register();
    void read_month_register();
    void read_year_register();
    void read_controls();
};
} // namespace DS3231
