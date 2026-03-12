#pragma once
#include "hardware/spi.h"
#include "pico/stdlib.h"

class SPIDevice
{
  private:
    const spi_inst_t *spi_;
    uint8_t cs_;

  public:
    explicit SPIDevice(const spi_inst_t *spi, uint8_t cs);
    SPIDevice() = delete;
    SPIDevice(const SPIDevice &) = delete;
    SPIDevice(SPIDevice &&) = delete;

  private:
    void toggleCs(uint8_t state) const;
    void select() const;
    void deselect() const;
};
