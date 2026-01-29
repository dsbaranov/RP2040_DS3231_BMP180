#pragma once

#include "hardware/i2c.h"
#include "pico/stdlib.h"
#include <cstdint>

class I2C
{
  public:
    I2C(i2c_inst_t *i2c, uint8_t scl_pin, uint8_t sda_pin);
    I2C() = delete;
    I2C(const I2C &) = delete;
    I2C(I2C &&) = delete;

    i2c_inst_t *get();

  private:
    static const uint32_t BAUDRATE = 400000u;

    i2c_inst *i2c_;

    void init(i2c_inst_t *i2c, uint8_t scl_pin, uint8_t sda_pin);
};