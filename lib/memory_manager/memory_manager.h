#pragma once
#include <iostream>
#include "spi/spi_flash_device.h"
#include "bmp180/bmp180.h"
#include "memory_manager/memory_manager_domain.h"

class MemoryManager
{
private:
    FlashDevice &flash_device_;
    BMP180::BMP180 &bmp180__ref_;

    uint32_t current_page_ = 0;
    uint32_t current_sector = 0;
    uint32_t current_block = 0;

    void set_max_pressure_bmp180(uint16_t value);
    void set_min_pressure_bmp180(uint16_t value);

public:
    explicit MemoryManager(FlashDevice &flash_device, BMP180::BMP180 &bmp180);
    MemoryManager() = delete;
    MemoryManager(const MemoryManager &) = delete;
    MemoryManager(MemoryManager &&) = delete;

    void EraseSector(uint32_t block, uint32_t sector);
    uint32_t ValidatePage() const;
    uint32_t ValidateSector() const;
    uint32_t ValidateBlock() const;
};