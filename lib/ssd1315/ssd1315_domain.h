#pragma once
#include <cstddef>
#include <cstdint>
namespace SSD1315::domain
{
enum class DisplaySizeType
{
    w128h32,
    w128h64
};

enum class DisplayAlignment
{
    Horizontal,
    Vertical,
    Page
};

struct Coordinate
{
    uint8_t x;
    uint8_t y;
};

struct Size
{
    Size(uint8_t width, uint8_t height);
    uint8_t width;
    uint8_t height;
    uint16_t area() const;
};

} // namespace SSD1315::domain