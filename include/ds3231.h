#pragma once
#include "ds3231_domain.h"
#include "ds3231_registers.h"
#include "hardware/i2c.h"

namespace DS3231
{
using namespace REGISTERS;

class DS3231
{
  public:
    DS3231(i2c_inst_t *i2c);

    DS3231() = delete;
    DS3231(const DS3231 &) = delete;
    DS3231(DS3231 &&) = delete;

    const uint8_t *buffer();

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

    domain::DateTime GetDateTime();
    const domain::DateTime &GetDateTimeConst();

  private:
    i2c_inst_t *i2c_;

    domain::DateTime datetime_;

    uint8_t data_buffer_[8u];

    void read_register(uint8_t reg, uint8_t n_regs);
    void write_register(uint8_t reg, uint8_t n_regs);

    void read_bulk_date_time_block();

    uint8_t decode_seconds(uint8_t value);
    uint8_t decode_minutes(uint8_t value);
    uint8_t decode_hours(uint8_t value);
    uint8_t decode_dow(uint8_t value);
    uint8_t decode_day(uint8_t value);
    uint8_t decode_month(uint8_t value);
    uint8_t decode_year(uint8_t value);

    void read_seconds_register();
    void read_minutes_register();
    void read_hours_register();
    void read_dow_register();
    void read_day_register();
    void read_month_register();
    void read_year_register();
};
}; // namespace DS3231
