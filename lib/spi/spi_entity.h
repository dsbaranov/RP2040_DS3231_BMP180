#pragma once
#include "hardware/spi.h"
#include "pico/stdlib.h"

class SPI
{
  public:
    SPI(spi_inst_t *spi, uint8_t rx, uint8_t tx, uint8_t sck, uint8_t cs);
    SPI() = delete;
    SPI(const SPI &) = delete;
    SPI(SPI &&) = delete;

    spi_inst_t *get();

  private:
    static const size_t BAUDRATE = 1000000u;
    spi_inst_t *spi_;
    uint8_t cs_;

    void init(spi_inst_t *spi, uint8_t rx, uint8_t tx, uint8_t sck, uint8_t cs);
};
