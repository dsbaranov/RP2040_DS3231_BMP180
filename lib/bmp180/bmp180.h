#pragma once

#include "bmp180_domain.h"
#include "bmp180_registers.h"
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
    void SetOSS(domain::MeasureDiscretion);
    void ReadData();

    float temperature();
    float pressure();

    void Flush();

  private:
    double temperature_ = 0.f, pressure_ = 0.f;
    domain::Coefficients coefficients;
    long temperature_raw = 0, pressure_raw = 0;
    domain::MeasureDiscretion oss_ = domain::MeasureDiscretion::x1;

    uint8_t GetOssIndex() const;

    void SendMeasureCommand(domain::MeasureCommand command);
    bool ReadMeasureFlag();
    bool ExecuteMeasure(domain::MeasureCommand command, uint8_t attempts);
    void GetTemperature();
    void GetPressure();
    void ExecuteCalculation();
};

} // namespace BMP180
