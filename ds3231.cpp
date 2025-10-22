#include "ds3231.h"

namespace DS3231
{

DS3231::DS3231(i2c_inst_t *i2c) : i2c_(i2c)
{
}

void DS3231::read_register(uint8_t reg, uint8_t n_regs)
{
    data_buffer_[0] = reg;
    i2c_write_blocking(i2c_, DS3231_ADDR, data_buffer_, 1, true);
    i2c_read_blocking(i2c_, DS3231_ADDR, data_buffer_ + 1, n_regs, false);
}

void DS3231::write_register([[maybe_unused]] uint8_t reg, [[maybe_unused]] uint8_t n_regs)
{
}

const uint8_t *DS3231::buffer()
{
    return data_buffer_;
}

}; // namespace DS3231
