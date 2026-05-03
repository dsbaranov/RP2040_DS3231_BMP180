#include "spi_device.h"

SPIDevice::SPIDevice(spi_inst_t *const spi, uint8_t cs) : spi_(spi), cs_(cs)
{
    gpio_init(cs);
    gpio_set_dir(cs, GPIO_OUT);
    deselect();
}

void SPIDevice::toggleCs(uint8_t state) const
{
    asm volatile("nop \n nop \n nop");
    gpio_put(cs_, state);
    asm volatile("nop \n nop \n nop");
}

void SPIDevice::select() const
{
    toggleCs(0);
}

void SPIDevice::deselect() const
{
    toggleCs(1);
}

void SPIDevice::flash_read(uint32_t addr, uint8_t *buf, size_t len)
{
    select();
    spi_write_blocking(spi_, form_cmd_buf(FLASH_CMD_READ, addr).data(), 4);
    spi_read_blocking(spi_, 0, buf, len);
    deselect();
}

void SPIDevice::flash_write_enable()
{
    select();
    uint8_t cmd = FLASH_CMD_WRITE_EN;
    spi_write_blocking(spi_, &cmd, 1);
    deselect();
}

void SPIDevice::flash_wait_done()
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

void SPIDevice::flash_sector_erase(uint32_t addr)
{
    flash_write_enable();
    select();
    spi_write_blocking(spi_, form_cmd_buf(FLASH_CMD_SECTOR_ERASE, addr).data(), 4);
    deselect();
    flash_wait_done();
}

void SPIDevice::flash_page_program(uint32_t addr, uint8_t data[])
{
    flash_write_enable();
    select();
    spi_write_blocking(spi_, form_cmd_buf(FLASH_CMD_PAGE_PROGRAM, addr).data(), 4);
    spi_write_blocking(spi_, data, FLASH_PAGE_SIZE);
    deselect();
    flash_wait_done();
}