#pragma once

#include "bmp180/bmp180_domain.h"
#include "bmp180/bmp180_registers.h"
#include "i2c/i2c_device.h"

namespace BMP180
{

class BMP180 : public I2CDevice
{
  public:
    BMP180(i2c_inst_t *i2c);
    BMP180() = delete;
    BMP180(const BMP180 &) = delete;
    BMP180(BMP180 &&) = delete;

    bool Ping();

    void GetCoefficients();

    void GetTemperature();
    void GetPressure();

  private:
    domain::Coefficients coefficients;

    void SendMeasureCommand(domain::MeasureCommand command, domain::MeasureDiscretion discretion);
};

} // namespace BMP180
