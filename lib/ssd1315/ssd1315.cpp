#include "ssd1315.h"
#include "ssd1315_registers.h"
namespace ssd1315
{
SSD1315::SSD1315(i2c_inst_t *i2c, uint8_t width, uint8_t height)
    : size_{width, height}, I2CDevice(i2c, REGISTERS::ADDR, size_.area())
{
}
} // namespace ssd1315