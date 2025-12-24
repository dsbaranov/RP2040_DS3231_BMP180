#pragma once

#include "hardware/i2c.h"
#include <vector>

static const size_t I2CDEVICE_DEFAULT_MAX_BUFFER_SIZE = 32u;
static const size_t I2CDEVICE_DEFAULT_TIMEOUT_US = 500000u;

class I2CDevice
{
  private:
    uint8_t device_address_;
    size_t timeout_us_;

  protected:
    i2c_inst_t *i2c_;

    size_t timeout_us = I2CDEVICE_DEFAULT_TIMEOUT_US;
    std::vector<uint8_t> data_buffer_;

    I2CDevice(i2c_inst_t *i2c, uint8_t device_address, size_t buffer_size, size_t timeout_us);
    I2CDevice(i2c_inst_t *i2c, uint8_t device_address, size_t buffer_size);
    I2CDevice(i2c_inst_t *i2c, uint8_t device_address);
    I2CDevice() = delete;
    I2CDevice(const I2CDevice &) = delete;
    I2CDevice(I2CDevice &&) = delete;

    void read_register(uint8_t reg, size_t n_regs);
    void write_register(uint8_t reg, size_t n_regs);

    ~I2CDevice();
};