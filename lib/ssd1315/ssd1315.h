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

  public:
    SSD1315(i2c_inst_t *i2c, domain::DisplaySizeType type);
};

} // namespace SSD1315