#pragma once

#include "hardware/i2c.h"
#include <vector>

static const size_t I2CDEVICE_DEFAULT_MAX_BUFFER_SIZE = 32u;
static const size_t I2CDEVICE_DEFAULT_TIMEOUT_US = 200000u;

class I2CDevice
{
protected:
  i2c_inst_t *i2c_;

  virtual void init() = 0;

private:
  uint8_t device_address_;

protected:
  size_t timeout_us = I2CDEVICE_DEFAULT_TIMEOUT_US;
  std::vector<uint8_t> data_buffer_;
  size_t buffer_size = 0;

private:
  size_t timeout_us_;

protected:
  I2CDevice(i2c_inst_t *i2c, uint8_t device_address, size_t buffer_size, size_t timeout_us);
  I2CDevice(i2c_inst_t *i2c, uint8_t device_address, size_t buffer_size);
  I2CDevice(i2c_inst_t *i2c, uint8_t device_address);
  I2CDevice() = delete;
  I2CDevice(const I2CDevice &) = delete;
  I2CDevice(I2CDevice &&) = delete;

  void read_register(uint8_t reg, size_t n_bytes);
  void write_register(uint8_t reg, size_t n_bytes);
  virtual ~I2CDevice() {}
};
