#pragma once
#include "hardware/spi.h"
#include "pico/stdlib.h"
namespace spi
{
class Spi
{
  public:
    static const uint32_t BAUDRATE = 1000000u;
    Spi(spi_inst_t *spi, uint8_t rx, uint8_t tx, uint8_t sck, uint8_t cs);
    Spi() = delete;
    Spi(const Spi &) = delete;
    Spi(Spi &&) = delete;

    const spi_inst_t *get();

    void select();
    void deselect();

  private:
    spi_inst_t *spi_;
    uint8_t cs_;

    void init(spi_inst_t *spi, uint8_t rx, uint8_t tx, uint8_t sck, uint8_t cs, uint32_t baudrate = BAUDRATE);

    static void toggleCsPin(uint8_t cs_pin, uint8_t state = 0);
};
}; // namespace spi
