#pragma once

#include "hardware/i2c.h"
#include "pico/stdlib.h"
#include <cstdint>
#include <cstring>

namespace example
{
#define OLED_ADDR 0x3C // Adresse I2C 7-bit standard (0x78 >> 1)
#define WIDTH 128
#define HEIGHT 64
#define PAGES (HEIGHT / 8)

// Simple 8x8 font (simplified for demonstration)
extern const uint8_t font8x8[95][8];

class SSD1315
{
  public:
    SSD1315(i2c_inst_t *i2c);

    void init();
    void clear();
    void display();
    void setPixel(int x, int y, bool on);
    void drawChar(int x, int y, char c);
    void drawString(int x, int y, const char *str);
    void drawStringCentered(int y, const char *str);
    void clearRect(int x, int y, int w, int h);

  private:
    i2c_inst_t *i2c;
    uint8_t buffer[WIDTH * PAGES];

    void sendCommand(uint8_t cmd);
    void sendData(uint8_t *data, size_t len);
};
}; // namespace example
