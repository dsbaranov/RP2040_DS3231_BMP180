#pragma once

#include "aht10_registers.h"
#include "i2c/i2c_device.h"

namespace AHT10
{

  class AHT10 : public I2CDevice
  {
  public:
    AHT10(i2c_inst_t *i2c) : I2CDevice(i2c, REGISTERS::DEVICE_ADDRESS, 6u, 20000)
    {
    }

    void init() override {}

    AHT10() = delete;
    AHT10(const AHT10 &) = delete;
    AHT10(AHT10 &&) = delete;

    void readData();

    float temperature() const;
    uint8_t humidity() const;

    const std::vector<uint8_t> &getBuffer() const
    {
      return data_buffer_;
    }

  private:
    float temperature_ = 0;
    uint8_t humidity_ = 0;

    static long byteToLongWithShift(uint8_t value, unsigned shift = 0);
  };

}; // namespace AHT10