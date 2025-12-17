#pragma once
#include <cstdint>

namespace BMP180::domain
{
struct Coefficients
{
    int16_t AC1 = 0;
    int16_t AC2 = 0;
    int16_t AC3 = 0;
    uint16_t AC4 = 0;
    uint16_t AC5 = 0;
    uint16_t AC6 = 0;
    int16_t B1 = 0;
    int16_t B2 = 0;
    int16_t MB = 0;
    int16_t MC = 0;
    int16_t MD = 0;
};

enum class MeasureCommand
{
    Temperature,
    Pressure,
};

enum class MeasureDiscretion
{
    x1,
    x2,
    x4,
    x8
};

struct MeasureControl
{
  private:
    static const uint8_t TEMPERATURE_CMD = 14;
    static const uint8_t PRESSURE_CMD = 20;

  public:
    MeasureDiscretion oss = MeasureDiscretion::x1;
    uint8_t cso = 1;
    MeasureCommand cmd = MeasureCommand::Temperature;

    uint8_t Pack();
};
} // namespace BMP180::domain