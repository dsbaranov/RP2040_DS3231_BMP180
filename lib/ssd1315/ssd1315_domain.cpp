#include "ssd1315_domain.h"

namespace SSD1315::domain
{
Size::Size(uint8_t _width, uint8_t _height) : width(_width), height(_height)
{
}

uint16_t Size::area() const
{
    return width * height;
}

} // namespace SSD1315::domain