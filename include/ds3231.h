#pragma once

#include "ds3231_registers.h"
#include "hardware/i2c.h"
#include "pico/stdlib.h"
#include <cstdint>

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

    uint8_t get_seconds();
    uint8_t get_minutes();
    uint8_t get_hours();
    uint8_t get_dow();
    uint8_t get_day();
    uint8_t get_month();
    uint8_t get_age();
    uint8_t get_year();

  private:
    i2c_inst_t *i2c_;

    uint8_t seconds_ = 0;
    uint8_t minutes_ = 0;
    uint8_t hours_ = 0;
    uint8_t dow_ = 0;
    uint8_t day_ = 0;
    uint8_t month_ = 0;
    uint8_t year_ = 0;
    bool is_meridial_ = false;
    bool is_pm_ = false;
    uint16_t age_ = 20;

    uint8_t data_buffer_[8u];

    void read_register(uint8_t reg, uint8_t n_regs);
    void write_register(uint8_t reg, uint8_t n_regs);
    void clear_register();

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
