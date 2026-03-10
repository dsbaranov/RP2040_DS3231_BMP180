#include "aht10.h"
#include <cmath>
namespace AHT10
{
void AHT10::readData()
{

    data_buffer_[0] = REGISTERS::MEASURE_CMD_HSB;
    data_buffer_[1] = REGISTERS::MEASURE_CMD_LSB;
    write_register(REGISTERS::CMD_MEASURE, 2);
    sleep_ms(100u);
    read_register(REGISTERS::CMD_MEASURE, 6);
    long raw_val = 0;
    double RH, RT;
    raw_val = byteToLongWithShift(data_buffer_.at(1), 12u) + byteToLongWithShift(data_buffer_.at(2), 4u) +
              byteToLongWithShift(((data_buffer_.at(3) >> 4) & 0x0F), 0);
    RH = static_cast<double>(raw_val);
    raw_val = 0;
    raw_val = byteToLongWithShift((data_buffer_.at(3) & 0x0F), 16) + byteToLongWithShift(data_buffer_.at(4), 8) +
              byteToLongWithShift(data_buffer_.at(5), 0);
    RT = static_cast<double>(raw_val);
    double divider = pow(2, 20);
    humidity_ = (RH / divider) * 100.;
    temperature_ = ((RT / divider) * 200.) - 50.;
}
double AHT10::temperature() const
{
    return temperature_;
}
double AHT10::humidity() const
{
    return humidity_;
}

long AHT10::byteToLongWithShift(uint8_t value, unsigned shift)
{
    shift %= 32u;
    return (((static_cast<long>(value)) & 0xFF) << shift);
}
} // namespace AHT10