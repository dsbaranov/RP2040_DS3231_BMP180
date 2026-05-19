#pragma once
#include <iostream>
#include "spi/spi_flash_device.h"
#include "bmp180/bmp180.h"
#include "memory_manager/memory_manager_domain.h"

class MemoryManager
{
private:
    FlashDevice &flash_device_ref_;
    BMP180::BMP180 &bmp180__ref_;

    uint16_t number_of_blocks_ = 0;
    uint16_t number_of_sectors_ = 0;
    uint16_t number_of_pages = 0;
    uint16_t page_size = 0;

    uint16_t current_page_ = 0;
    uint16_t current_sector = 0;
    uint16_t current_block = 0;

    void set_max_pressure_bmp180(uint16_t value);
    void set_min_pressure_bmp180(uint16_t value);

public:
    MemoryManager(FlashDevice &flash_device, BMP180::BMP180 &bmp180);
};