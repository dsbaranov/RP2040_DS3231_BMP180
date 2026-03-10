#pragma once
#include "hardware/spi.h"
#include "pico/stdlib.h"

class SPI
{
  public:
    static const uint32_t BAUDRATE = 1000000u;
    SPI(spi_inst_t *spi, uint8_t rx, uint8_t tx, uint8_t sck, uint8_t cs);
    SPI() = delete;
    SPI(const SPI &) = delete;
    SPI(SPI &&) = delete;

    const spi_inst_t *get();

    void select() const;
    void deselect() const;

    int __not_in_flash_func(return_1)()
    {
        return 1;
    }

  private:
    spi_inst_t *spi_;
    uint8_t cs_;

    void init(spi_inst_t *spi, uint8_t rx, uint8_t tx, uint8_t sck, uint8_t cs, uint32_t baudrate = BAUDRATE);

    static void toggleCsPin(uint8_t cs_pin, uint8_t state = 0);
};
