#pragma once
#include "i2c/i2c_device.h"
#include "ssd1315_domain.h"
#include <vector>
namespace ssd1315
{

class SSD1315 : public I2CDevice
{

  private:
    domain::Size size_;
    std::vector<uint8_t> display_;

  public:
    SSD1315(domain::DisplaySizeType type, domain::DisplayAlignment alignment);
};

} // namespace ssd1315