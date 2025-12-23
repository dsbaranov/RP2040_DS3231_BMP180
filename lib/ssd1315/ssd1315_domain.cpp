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

uint16_t Size::getArea() const
{
    return area_;
}

Size &Size::setWidth(uint8_t value)
{
    width_ = value;
    CalculateArea();
    return *this;
}

Size &Size::setHeight(uint8_t value)
{
    height_ = value;
    CalculateArea();
    return *this;
}

} // namespace ssd1315::domain