#pragma once

#include "ds3231_regs.h"
#include "hardware/i2c.h"
#include "pico/stdlib.h"
#include <cstdint>

namespace DS3231
{
using namespace registers;

class DS3231
{
  public:
    DS3231() = delete;
    DS3231(const DS3231 &) = delete;
    DS3231(DS3231 &&) = delete;

    DS3231(i2c_inst_t *i2c);

    void read_register(uint8_t reg, uint8_t n_regs);

    void write_register(uint8_t reg, uint8_t n_regs);

    const uint8_t *buffer();

  private:
    uint8_t second_ = 0;
    uint8_t minute_ = 0;
    uint8_t hour_ = 0;
    uint8_t day_ = 0;
    uint8_t month_ = 0;
    uint8_t year_ = 0;
    bool is_pm = false;

    uint8_t data_buffer_[8u];

    i2c_inst_t *i2c_;
};
}; // namespace DS3231
