#pragma once

#include "spi/spi_flash_device.h"
#include "w25q32bv/w25q32bv_common.h"

#define FLASH_STATUS_BUSY_MASK 0x01

class W25Q32BV : public FlashDevice
{
private:
    static const uint8_t FLASH_CMD_PAGE_PROGRAM = 0x02;
    static const uint8_t FLASH_CMD_READ = 0x03;
    static const uint8_t FLASH_CMD_STATUS = 0x05;
    static const uint8_t FLASH_CMD_WRITE_EN = 0x06;
    static const uint8_t FLASH_CMD_SECTOR_ERASE = 0x20;

    static const uint32_t number_of_blocks_ = 64;
    static const uint32_t number_of_sectors_ = 16;
    static const uint32_t number_of_pages_ = 16;
    static const uint32_t page_size_ = 256;

public:
    W25Q32BV(spi_inst_t *const spi, uint8_t cs) : FlashDevice(spi, cs) {};

    uint32_t get_number_of_blocks() const override;
    uint32_t get_number_of_sectors() const override;
    uint32_t get_number_of_pages() const override;
    uint32_t get_page_size() const override;
    void flash_read(uint32_t addr, uint8_t *buf, size_t len) override;
    void flash_write_enable() override;
    void flash_wait_done() override;
    void flash_sector_erase(uint32_t addr) override;
    void flash_page_program(uint32_t addr, uint8_t data[]) override;

    ~W25Q32BV() {};
};
