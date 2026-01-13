#include "ssd1315.h"

#include "ssd1315_registers.h"
#include <algorithm>
namespace SSD1315
{
void SSD1315::setPixel(uint8_t x, uint8_t y, bool on)
{
    if (x >= size_.width || y >= size_.height)
        return;
    uint8_t shift = y % PAGES;
    uint16_t index = y / PAGES * size_.width + x;
    if (on)
    {
        data_buffer_[index] |= (1 << shift);
    }
    else
    {
        data_buffer_[index] &= ~(1 << shift);
    }
}

void SSD1315::sendCmd(uint8_t command)
{
    data_buffer_[0] = command;
    write_register(0x00, 1);
}

SSD1315::SSD1315(i2c_inst_t *i2c, domain::DisplaySizeType type)
    : size_{uint8_t(128), uint8_t(32) * (static_cast<uint8_t>(type) + uint8_t(1))},
      I2CDevice(i2c, REGISTERS::ADDR, 129u)
{
    display_.resize(size_.area() / PAGES, 0u);
    display_size_ = display_.size();
}

void SSD1315::Init()
{
    sendCmd(0xAE); // Display off
    sendCmd(0xD5);
    sendCmd(0x80); // Set display clock divide ratio
    sendCmd(0xA8);
    sendCmd(0x3F); // Set multiplex ratio
    sendCmd(0xD3);
    sendCmd(0x00); // Set display offset
    sendCmd(0x40); // Set start line address
    sendCmd(0x8D);
    sendCmd(0x14); // Charge pump
    sendCmd(0x20);
    sendCmd(0x00); // Memory addressing mode
    sendCmd(0xA1); // Set segment re-map
    sendCmd(0xC8); // Set COM output scan direction
    sendCmd(0xDA);
    sendCmd(0x12); // Set COM pins hardware configuration
    sendCmd(0x81);
    sendCmd(0xCF); // Set contrast control
    sendCmd(0xD9);
    sendCmd(0xF1); // Set pre-charge period
    sendCmd(0xDB);
    sendCmd(0x40); // Set VCOMH
    sendCmd(0xA4); // Entire display on
    sendCmd(0xA6); // Set normal display
    sendCmd(0xAF); // Display on
}

void SSD1315::draw()
{
    for (int page = 0; page < PAGES; ++page)
    {
        sendCmd(0xB0 + page); // Set page address
        sendCmd(0x00);        // Set lower column start address
        sendCmd(0x10);        // Set higher column start address
        auto begin = display_.begin() + (page * (size_.width));
        size_t begin_ = std::distance(display_.begin(), begin);
        auto end = begin + size_.width;
        size_t end_ = std::distance(display_.begin(), end);
        std::copy(begin, end, data_buffer_.begin());
        write_register(0x40, size_.width);
    }
}

SSD1315::~SSD1315()
{
    display_.clear();
}
} // namespace SSD1315