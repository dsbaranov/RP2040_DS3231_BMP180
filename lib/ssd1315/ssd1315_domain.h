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
  private:
    uint8_t width_;
    uint8_t height_;
    uint16_t area_;
    void CalculateArea();

  public:
    Size(uint8_t width, uint8_t height);
    uint8_t getWidth() const;
    uint8_t getHeight() const;
    uint16_t getArea() const;
    Size &setWidth(uint8_t value);
    Size &setHeight(uint8_t value);
};

} // namespace ssd1315::domain