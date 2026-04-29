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
  explicit SPIDevice(const spi_inst_t *spi, uint8_t cs);
  SPIDevice() = delete;
  SPIDevice(const SPIDevice &) = delete;
  SPIDevice(SPIDevice &&) = delete;

private:
  void toggleCs(uint8_t state) const;
  void select() const;
  void deselect() const;

  void
  __not_in_flash_func(flash_read)(uint32_t addr, uint8_t *buf, size_t len)
  {
    select();
    spi_write_blocking(spi_, form_cmd_buf(FLASH_CMD_READ, addr).data(), 4);
    spi_read_blocking(spi_, 0, buf, len);
    deselect();
  }

  void __not_in_flash_func(flash_write_enable)()
  {
    select();
    uint8_t cmd = FLASH_CMD_WRITE_EN;
    spi_write_blocking(spi_, &cmd, 1);
    deselect();
  }

  void __not_in_flash_func(flash_wait_done)()
  {
    uint8_t status;
    do
    {
      select();
      uint8_t buf[2] = {FLASH_CMD_STATUS, 0};
      spi_write_read_blocking(spi_, buf, buf, 2);
      deselect();
      status = buf[1];
    } while (status & FLASH_STATUS_BUSY_MASK);
  }

  void __not_in_flash_func(flash_sector_erase)(uint32_t addr)
  {
    flash_write_enable();
    select();
    spi_write_blocking(spi_, form_cmd_buf(FLASH_CMD_SECTOR_ERASE, addr).data(), 4);
    deselect();
    flash_wait_done();
  }

  void __not_in_flash_func(flash_page_program)(uint32_t addr, uint8_t data[])
  {
    flash_write_enable();
    select();
    spi_write_blocking(spi_, form_cmd_buf(FLASH_CMD_PAGE_PROGRAM, addr).data(), 4);
    spi_write_blocking(spi_, data, FLASH_PAGE_SIZE);
    deselect();
    flash_wait_done();
  }
};
