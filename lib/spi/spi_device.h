#pragma once
#include "hardware/spi.h"
#include "pico/stdlib.h"
#include "spi_common.h"
#include <vector>

#define FLASH_PAGE_SIZE 256
#define FLASH_SECTOR_SIZE 4096

#define FLASH_CMD_PAGE_PROGRAM 0x02
#define FLASH_CMD_READ 0x03
#define FLASH_CMD_STATUS 0x05
#define FLASH_CMD_WRITE_EN 0x06
#define FLASH_CMD_SECTOR_ERASE 0x20

#define FLASH_STATUS_BUSY_MASK 0x01

class SPIDevice
{
private:
  spi_inst_t *const spi_;
  uint8_t cs_;

public:
  explicit SPIDevice(spi_inst_t *const spi, uint8_t cs);
  SPIDevice() = delete;
  SPIDevice(const SPIDevice &) = delete;
  SPIDevice(SPIDevice &&) = delete;

private:
  void toggleCs(uint8_t state) const;
  void select() const;
  void deselect() const;

  void
      __not_in_flash_func(flash_read)(uint32_t addr, uint8_t *buf, size_t len);
  void __not_in_flash_func(flash_write_enable)();
  void __not_in_flash_func(flash_wait_done)();
  void __not_in_flash_func(flash_sector_erase)(uint32_t addr);
  void __not_in_flash_func(flash_page_program)(uint32_t addr, uint8_t data[]);
};
