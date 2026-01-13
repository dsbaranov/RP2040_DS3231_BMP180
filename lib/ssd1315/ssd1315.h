#pragma once
#include <vector>

#include "i2c/i2c_device.h"
#include "ssd1315_domain.h"
namespace SSD1315
{

class SSD1315 : public I2CDevice
{
  private:
    const static uint8_t PAGES = 8u;

    domain::Size size_;
    std::vector<uint8_t> display_;

    void sendCmd(uint8_t command);

    size_t display_size_;

  public:
    SSD1315(i2c_inst_t *i2c, domain::DisplaySizeType type);
    SSD1315() = delete;
    SSD1315(const SSD1315 &) = delete;
    SSD1315(SSD1315 &&) = delete;

    void Init();

    void draw();

    void setPixel(uint8_t x, uint8_t y, bool on = false);

    ~SSD1315();
};

} // namespace SSD1315