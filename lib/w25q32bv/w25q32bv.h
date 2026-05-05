#pragma once

#include "spi/spi_device.h"
#include "w25q32bv/w25q32bv_common.h"

#define FLASH_PAGE_SIZE 256
#define FLASH_SECTOR_SIZE 4096

static const uint8_t FLASH_CMD_PAGE_PROGRAM = 0x02;
static const uint8_t FLASH_CMD_READ = 0x03;
static const uint8_t FLASH_CMD_STATUS = 0x05;
static const uint8_t FLASH_CMD_WRITE_EN = 0x06;
static const uint8_t FLASH_CMD_SECTOR_ERASE = 0x20;

#define FLASH_STATUS_BUSY_MASK 0x01

class W25Q32BV : protected SPIDevice
{
private:
public:
    W25Q32BV(spi_inst_t *spi, uint8_t cs) : SPIDevice(spi, cs) {};
    ~W25Q32BV() {};

    void
        __not_in_flash_func(flash_read)(uint32_t addr, uint8_t *buf, size_t len);
    void __not_in_flash_func(flash_write_enable)();
    void __not_in_flash_func(flash_wait_done)();
    void __not_in_flash_func(flash_sector_erase)(uint32_t addr);
    void __not_in_flash_func(flash_page_program)(uint32_t addr, uint8_t data[]);
};
