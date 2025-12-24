#pragma once
#include <cstddef>
#include <cstdint>
namespace ssd1315::domain
{
enum class DisplaySizeType
{
    w128h64,
    w128h32
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
    uint8_t width;
    uint8_t height;
    uint16_t area() const;
};

} // namespace ssd1315::domain