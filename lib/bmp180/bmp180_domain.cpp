#include "bmp180_domain.h"

namespace BMP180::domain
{
uint8_t MeasureControl::Pack()
{
    uint8_t _cmd;
    if (cmd == MeasureCommand::Temperature)
    {
        _cmd = TEMPERATURE_CMD;
    }
    else
    {
        _cmd = PRESSURE_CMD;
    }
    if (cmd == MeasureCommand::Temperature)
    {
        oss = MeasureDiscretion::x1;
    }
    return (((static_cast<uint8_t>(oss) << 1) | 0x01) << 5u) | _cmd;
}
} // namespace BMP180::domain
