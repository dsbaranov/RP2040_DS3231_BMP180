#pragma once
#include "spi/spi_device.h"
class FlashDevice : SPIDevice
{
public:
    FlashDevice(spi_inst_t *const spi, uint8_t cs) : SPIDevice(spi, cs) {}

    spi_inst_t *getSpiPtr() const;
    void select();
    void deselect();

    virtual uint32_t get_number_of_blocks() const = 0;
    virtual uint32_t get_number_of_sectors() const = 0;
    virtual uint32_t get_number_of_pages() const = 0;
    virtual uint32_t get_page_size() const = 0;
    virtual void flash_read(uint32_t addr, uint8_t *buf, size_t len) = 0;
    virtual void flash_write_enable() = 0;
    virtual void flash_wait_done() = 0;
    virtual void flash_sector_erase(uint32_t addr) = 0;
    virtual void flash_page_program(uint32_t addr, uint8_t data[], uint32_t length) = 0;

    virtual ~FlashDevice() {}
};