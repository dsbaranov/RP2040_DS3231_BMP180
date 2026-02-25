#pragma once
#include "i2c/i2c_device.h"
#include "ssd1315_domain.h"

#include <string>
#include <vector>
namespace SSD1315
{

class SSD1315 : public I2CDevice
{
  private:
    domain::Size size_;
    const static uint8_t PAGES = 8u;

    std::vector<uint8_t> display_;

    domain::Coordinate cursor_ = {0, 0};

    void sendCommand(uint8_t command);
    void drawByteVector(uint8_t x, uint8_t y, const std::vector<uint8_t> &src);

  public:
    SSD1315(i2c_inst_t *i2c, domain::DisplaySizeType type);
    SSD1315() = delete;
    SSD1315(const SSD1315 &) = delete;
    SSD1315(SSD1315 &&) = delete;

    SSD1315 &init();

    SSD1315 &draw();
    SSD1315 &setPixel(uint8_t x, uint8_t y, uint8_t on = false);
    SSD1315 &setCursor(uint8_t x, uint8_t y);
    SSD1315 &setChar(uint8_t x, uint8_t y, char c);
    SSD1315 &setChar(char c);
    SSD1315 &setString(std::string &&str);
    SSD1315 &setString(const std::string &str);
    SSD1315 &setString(uint8_t x, uint8_t y, const std::string &str);
    SSD1315 &setDegree(uint8_t x, uint8_t y);
    SSD1315 &setDegree();
    SSD1315 &clearRect();
    SSD1315& clearRect(uint8_t x, uint8_t y, uint8_t width, uint8_t height);
    SSD1315 &clear();

    ~SSD1315();
};

} // namespace SSD1315