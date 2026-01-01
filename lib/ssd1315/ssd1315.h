#pragma once
#include <vector>

#include "i2c/i2c_device.h"
#include "ssd1315_domain.h"
namespace SSD1315
{

class SSD1315 : public I2CDevice
{
  private:
    domain::Size size_;
    std::vector<uint8_t> display_;

    void SetPixel(uint8_t x, uint8_t y, bool on = false);

  public:
    SSD1315(i2c_inst_t *i2c, domain::DisplaySizeType type);
    SSD1315() = delete;
    SSD1315(const SSD1315 &) = delete;
    SSD1315(SSD1315 &&) = delete;
    ~SSD1315();
};

} // namespace SSD1315