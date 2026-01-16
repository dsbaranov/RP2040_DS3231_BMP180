#include "ssd1315.h"
#include "ssd1315_font.h"
#include "ssd1315_registers.h"
#include <algorithm>
namespace SSD1315
{
SSD1315 &SSD1315::setPixel(uint8_t x, uint8_t y, bool on)
{
    if (x >= size_.width || y >= size_.height)
        return *this;
    x += 2;
    uint8_t shift = y % PAGES;
    uint16_t index = y / PAGES * size_.width + x;
    if (on)
    {
        display_[index] |= (1 << shift);
    }
    else
    {
        display_[index] &= ~(1 << shift);
    }
    return *this;
}

SSD1315 &SSD1315::setCursor(uint8_t x, uint8_t y)
{
    cursor_.x = std::min(x, size_.width);
    cursor_.y = std::min(y, size_.height);
    return *this;
}

SSD1315 &SSD1315::setChar(uint8_t x, uint8_t y, char c)
{
    const auto entry_it = font::font.find(c);
    if (entry_it == font::font.end())
        return *this;
    size_t char_width = entry_it->second.size();
    for (size_t column = 0; column < char_width; ++column)
    {
        for (uint8_t shift = 0; shift < 8u; ++shift)
        {
            setPixel(x + column, y + shift, static_cast<bool>((entry_it->second.at(column) >> shift) & 0x01));
        }
    }
    cursor_.x += char_width;
    if (cursor_.x >= 128)
    {
        cursor_.x = 0;
        cursor_.y += 8u;
    }
    return *this;
}

SSD1315 &SSD1315::setChar(char c)
{
    setChar(cursor_.x, cursor_.y, c);
    return *this;
}

SSD1315 &SSD1315::setString(std::string &&str)
{
    for (char c : str)
    {
        setChar(std::move(c));
    }
    return *this;
}

SSD1315 &SSD1315::setString(uint8_t x, uint8_t y, const std::string &str)
{
    for (char c : str)
    {
        setChar(c);
    }
    return *this;
}

void SSD1315::sendCmd(uint8_t command)
{
    data_buffer_[0] = command;
    write_register(0x00, 1);
}

SSD1315::SSD1315(i2c_inst_t *i2c, domain::DisplaySizeType type)
    : size_(131, type == domain::DisplaySizeType::w128h64 ? 64 : 32), I2CDevice(i2c, REGISTERS::ADDR, 129u),
      display_(size_.area() / PAGES, 0), cursor_{0, 0}
{
    display_size_ = display_.size();
}

SSD1315 &SSD1315::init()
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
    return *this;
}

SSD1315 &SSD1315::draw()
{
    for (int page = 0; page < PAGES; ++page)
    {
        sendCmd(0xB0 + page); // Set page address
        sendCmd(0x00);        // Set lower column start address
        sendCmd(0x10);        // Set higher column start address
        auto begin = display_.begin() + (page * (size_.width));
        size_t begin_ = std::distance(display_.begin(), begin);
        auto end = begin + size_.width - 1;
        size_t end_ = std::distance(display_.begin(), end);
        std::copy(begin, end, data_buffer_.begin());
        write_register(0x40, size_.width);
    }
    return *this;
}

SSD1315::~SSD1315()
{
    display_.clear();
}
} // namespace SSD1315