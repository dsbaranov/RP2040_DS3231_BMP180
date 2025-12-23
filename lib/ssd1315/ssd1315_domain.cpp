#include "ssd1315_domain.h"

namespace ssd1315::domain
{

void Size::CalculateArea()
{
    area_ = width_ * height_;
}
Size::Size(uint8_t width, uint8_t height) : width_(width), height_(height)
{
    CalculateArea();
}

uint8_t Size::getWidth() const
{
    return width_;
}

uint8_t Size::getHeight() const
{
    return height_;
}
} // namespace ssd1315::domain