#pragma once
#include "hardware/spi.h"
#include "pico/stdlib.h"

class SPI
{
public:
  explicit SPI(spi_inst_t *spi, uint8_t rx, uint8_t tx, uint8_t sck);
  SPI() = delete;
  SPI(const SPI &) = delete;
  SPI(SPI &&) = delete;

  spi_inst_t *get();

private:
  static const uint32_t BAUDRATE = 1000000u;
  spi_inst_t *spi_;
  void init(spi_inst_t *spi, uint8_t rx, uint8_t tx, uint8_t sck, uint32_t baudrate = BAUDRATE);
  static void toggleCsPin(uint8_t cs_pin, uint8_t state = 0);
};
