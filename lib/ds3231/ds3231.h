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
  private:
    domain::IDateTimeDetailed datetime_;
    domain::IAlarm1 alarm1_;
    domain::IAlarm2 alarm2_;

  public:
    domain::Controls Controls;
    domain::State State;

    DS3231(i2c_inst_t *i2c);
    DS3231() = delete;
    DS3231(const DS3231 &) = delete;
    DS3231(DS3231 &&) = delete;

    void init();

    uint8_t getSeconds();
    uint8_t getMinutes();
    uint8_t getHours();
    uint8_t getDow();
    uint8_t getDay();
    uint8_t getMonth();
    uint8_t getAge();
    uint8_t getYear();
    std::string getFormattedSeconds();
    std::string getFormattedMinutes();
    std::string getFormattedHours();
    std::string getFormattedDay();
    std::string getFormattedMonth();
    std::string getFormattedYear();

    DS3231 &setSeconds(uint8_t value = 0);
    DS3231 &setMinutes(uint8_t value = 0);
    DS3231 &setHours(uint8_t value = 0, uint8_t is_meridial = 0, uint8_t is_am = 0);
    DS3231 &setDow(uint8_t value);
    DS3231 &setDay(uint8_t value);
    DS3231 &setMonth(uint8_t value);
    DS3231 &setYear(uint16_t value);

    template <typename T> DS3231 &setAlarm(T &&interface)
    {
        set_alarm(std::forward<T>(interface));
        return *this;
    }

    void readAlarm1();
    domain::IAlarm1 &Alarm1();

    void readAlarm2();
    domain::IAlarm2 &Alarm2();

    void setDateTimeBlock(const domain::IDateTimeDetailed &datetime);

    domain::IDateTimeDetailed getDateTime();
    const domain::IDateTimeDetailed &getDateTimeConst() const;

    void readControls();
    DS3231 &setControls();

    void readState();
    DS3231 &setState();

    const std::vector<uint8_t> &getBuffer()
    {
        return data_buffer_;
    }

  private:
    void read_bulk_date_time_block();
    static uint8_t decode_seconds(uint8_t seconds);
    static uint8_t decode_minutes(uint8_t minutes);
    static domain::IHourData decode_hours(uint8_t hours);
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
    void read_state();
    void set_state();
};
} // namespace DS3231
