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
    void readCoefficients();
    void SetOSS(domain::MeasureDiscretion);
    void ReadData(bool including_pressure = true);

    float temperature() const;
    uint16_t pressure() const;

    void Flush();

    void init() override;
    uint16_t getMin() const;
    uint16_t getMax() const;
    void setMin(uint16_t value);
    void setMax(uint16_t value);

  private:
    uint16_t pressure_min_ = 999, pressure_max_ = 0;
    double temperature_ = 0.;
    uint16_t pressure_ = 0;
    domain::Coefficients coefficients;
    long temperature_raw = 0, pressure_raw = 0;
    domain::MeasureDiscretion oss_ = domain::MeasureDiscretion::x1;

    uint8_t getOssIndex() const;

    void send_measure_command(domain::MeasureCommand command);
    bool read_measure_flag();
    bool measure(domain::MeasureCommand command, uint8_t attempts);
    void read_temperature();
    void read_pressure();
    void calculate(bool including_pressure = true);
  };

} // namespace BMP180
