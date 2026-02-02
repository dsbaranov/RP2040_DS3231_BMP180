#include "ssd1315.h"
#include "ssd1315_font.h"
#include "ssd1315_registers.h"
#include <algorithm>
#include <cctype>
#include <cmath>

namespace SSD1315
{
SSD1315 &SSD1315::setPixel(uint8_t x, uint8_t y, uint8_t on)
{
    x += 2;
    if (x >= size_.width || y >= size_.height)
        return *this;
    uint8_t shift = y % PAGES;
    uint16_t index = y / PAGES * size_.width + x;
    if (on != 0)
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
    drawByteVector(x, y, entry_it->second);
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

SSD1315 &SSD1315::setString(const std::string &str)
{
    for (char c : str)
    {
        setChar(std::move(c));
    }
    return *this;
}

SSD1315 &SSD1315::setString(uint8_t x, uint8_t y, const std::string &str)
{
    setCursor(x, y);
    for (char c : str)
    {
        setChar(c);
    }
    return *this;
}

SSD1315 &SSD1315::setDegree(uint8_t x, uint8_t y)
{
    drawByteVector(x, y, font::deg);
    return *this;
}

SSD1315 &SSD1315::setDegree()
{
    setDegree(cursor_.x, cursor_.y);
    return *this;
}

SSD1315 &SSD1315::clearRect()
{
    std::fill(display_.begin(), display_.end(), 0);
    return *this;
}

SSD1315 &SSD1315::clear()
{
    clearRect();
    render();
    return *this;
}

void SSD1315::sendCommand(uint8_t command)
{
    data_buffer_[0] = command;
    write_register(0x00, 1);
}

void SSD1315::drawByteVector(uint8_t x, uint8_t y, const std::vector<uint8_t> &src)
{
    size_t char_width = src.size();
    for (size_t column = 0; column < char_width; ++column)
    {
        for (uint8_t shift = 0; shift < 8u; ++shift)
        {
            setPixel(x + column, y + shift, (src.at(column) >> shift) & 0x01);
        }
    }
    cursor_.x += char_width;
    if (cursor_.x >= 128)
    {
        cursor_.x = 0;
        cursor_.y += 8u;
    }
}

SSD1315::SSD1315(i2c_inst_t *i2c, domain::DisplaySizeType type)
    : I2CDevice(i2c, REGISTERS::ADDR, 129u), size_(131, type == domain::DisplaySizeType::w128h64 ? 64 : 32),
      display_(size_.area() / PAGES, 0)
{
}

SSD1315 &SSD1315::init()
{
    using namespace REGISTERS;
    sendCommand(CMD_DISPLAY); // Display off
    sendCommand(CMD_DISPLAY_CLOCK_DIVIDE_RATIO);
    sendCommand(0x80); // Set display clock divide ratio
    sendCommand(CMD_MULTIPLEX_RATIO);
    sendCommand(0x3F); // Set multiplex ratio
    sendCommand(CMD_DISPLAY_OFFSET);
    sendCommand(0x00);                   // Set display offset
    sendCommand(CMD_DISPLAY_START_LINE); // Set start line address
    sendCommand(CMD_CHARGE_PUMP);
    sendCommand(0x14); // Charge pump
    sendCommand(CMD_MEMO_ADR_MODE);
    sendCommand(0x00); // Memory addressing mode
    sendCommand(0xA1); // Set segment re-map
    sendCommand(0xC8); // Set COM output scan direction
    sendCommand(CMD_COM_PINS_HW_CONF);
    sendCommand(0x12); // Set COM pins hardware configuration
    sendCommand(CMD_CONTRAST_CTRL);
    sendCommand(0xCF); // Set contrast control
    sendCommand(CMD_PRECHARGE_PERIOD);
    sendCommand(0xF1); // Set pre-charge period
    sendCommand(CMD_VCOMH_SELECT_LEVEL);
    sendCommand(0x40);                       // Set VCOMH
    sendCommand(CMD_ENTIRE_DISPLAY_ON);      // Entire display on
    sendCommand(CMD_INVERSE_DISPLAY_NORMAL); // Set normal display
    sendCommand(0xAF);                       // Display on
    return *this;
}

SSD1315 &SSD1315::render()
{
    for (int page = 0; page < PAGES; ++page)
    {
        sendCommand(0xB0 + page); // Set page address
        sendCommand(0x00);        // Set lower column start address
        sendCommand(0x10);        // Set higher column start address
        auto begin = display_.begin() + (page * (size_.width));
        auto end = begin + size_.width - 1;
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