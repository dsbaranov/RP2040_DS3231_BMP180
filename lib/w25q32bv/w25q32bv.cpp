#include "w25q32bv.h"

uint32_t W25Q32BV::get_number_of_blocks() const
{
    return number_of_blocks_;
}

uint32_t W25Q32BV::get_number_of_sectors() const
{
    return number_of_sectors_;
}

uint32_t W25Q32BV::get_number_of_pages() const
{
    return number_of_pages_;
}

uint32_t W25Q32BV::get_page_size() const
{
    return page_size_;
}

void W25Q32BV::flash_read(uint32_t addr, uint8_t *buf, size_t len)
{
    select();
    spi_write_blocking(getSpiPtr(), form_cmd_buf(FLASH_CMD_READ, addr).data(), 4);
    spi_read_blocking(getSpiPtr(), 0, buf, len);
    deselect();
}

void W25Q32BV::flash_write_enable()
{
    select();
    uint8_t cmd = FLASH_CMD_WRITE_EN;
    spi_write_blocking(getSpiPtr(), &cmd, 1);
    deselect();
}

void W25Q32BV::flash_wait_done()
{
    uint8_t status;
    do
    {
        select();
        uint8_t buf[2] = {FLASH_CMD_STATUS, 0};
        spi_write_read_blocking(getSpiPtr(), buf, buf, 2);
        deselect();
        status = buf[1];
    } while (status & FLASH_STATUS_BUSY_MASK);
}

void W25Q32BV::flash_sector_erase(uint32_t addr)
{
    if (addr % (page_size_ * number_of_pages_) != 0 || addr >= (page_size_ * number_of_pages_ * number_of_sectors_ * number_of_blocks_))
    {
        return;
    }
    else
    {
        flash_write_enable();
        select();
        spi_write_blocking(getSpiPtr(), form_cmd_buf(FLASH_CMD_SECTOR_ERASE, addr).data(), 4);
        deselect();
        flash_wait_done();
    }
}

void W25Q32BV::flash_page_program(uint32_t addr, uint8_t data[])
{
    flash_write_enable();
    select();
    spi_write_blocking(getSpiPtr(), form_cmd_buf(FLASH_CMD_PAGE_PROGRAM, addr).data(), 4);
    spi_write_blocking(getSpiPtr(), data, page_size_);
    deselect();
    flash_wait_done();
}