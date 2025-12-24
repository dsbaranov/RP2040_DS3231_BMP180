#include "ssd1315_domain.h"

namespace ssd1315::domain
{

uint16_t Size::area() const
{
    return width * height;
}

} // namespace ssd1315::domain