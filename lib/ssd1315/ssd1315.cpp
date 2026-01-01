#include "ssd1315.h"

#include "ssd1315_registers.h"
namespace SSD1315
{
void SSD1315::SetPixel(uint8_t x, uint8_t y, bool on)
{
}

SSD1315::SSD1315(i2c_inst_t *i2c, domain::DisplaySizeType type)
    : size_{uint8_t(128), uint8_t(32) * (static_cast<uint8_t>(type) + 1)}, I2CDevice(i2c, REGISTERS::ADDR, size_.area())
{
}
SSD1315::~SSD1315()
{
    display_.clear();
}
} // namespace SSD1315