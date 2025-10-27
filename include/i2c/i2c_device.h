#pragma once

#include "hardware/i2c.h"

#define I2CDEVICE_MAX_BUFFER_SIZE 8u
#define I2CDEVICE_TIMEOUT_US 500000u

class I2CDevice
{
  private:
    uint8_t device_address_;

  protected:
    I2CDevice(i2c_inst_t *i2c, uint8_t device_address);
    I2CDevice() = delete;
    I2CDevice(const I2CDevice &) = delete;
    I2CDevice(I2CDevice &&) = delete;

  public:
    i2c_inst_t *i2c_;
    uint8_t data_buffer_[I2CDEVICE_MAX_BUFFER_SIZE];

    void read_register(uint8_t reg, uint8_t n_regs);
    void write_register(uint8_t reg, uint8_t n_regs);
};