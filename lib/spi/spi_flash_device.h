#pragma once
#include "spi/spi_device.h"
class FlashDevice : SPIDevice
{
protected:
    FlashDevice(spi_inst_t *const spi, uint8_t cs) : SPIDevice(spi, cs) {}

    spi_inst_t *getSpi() const;
    void select();
    void deselect();

    virtual void flash_read(uint32_t addr, uint8_t *buf, size_t len) = 0;
    virtual void flash_write_enable() = 0;
    virtual void flash_wait_done() = 0;
    virtual void flash_sector_erase(uint32_t addr) = 0;
    virtual void flash_page_program(uint32_t addr, uint8_t data[]) = 0;

    virtual ~FlashDevice() {}
};