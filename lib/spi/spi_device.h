#pragma once
#include "hardware/spi.h"
#include "pico/stdlib.h"
#include "spi_common.h"

class SPIDevice
{
protected:
  spi_inst_t *spi_;
  uint8_t cs_;

  explicit SPIDevice(spi_inst_t *spi, uint8_t cs);
  SPIDevice() = delete;
  SPIDevice(const SPIDevice &) = delete;
  SPIDevice(SPIDevice &&) = delete;

  void toggleCs(uint8_t state) const;
  void select() const;
  void deselect() const;
};
