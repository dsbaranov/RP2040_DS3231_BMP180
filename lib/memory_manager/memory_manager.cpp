#include "memory_manager.h"

void MemoryManager::set_max_pressure_bmp180(uint16_t value)
{
    bmp180__ref_.setMax(value);
}

void MemoryManager::set_min_pressure_bmp180(uint16_t value)
{
    bmp180__ref_.setMin(value);
}

MemoryManager::MemoryManager(FlashDevice &flash_device, BMP180::BMP180 &bmp180)
    : flash_device_(flash_device),
      bmp180__ref_(bmp180)
{
}

void MemoryManager::EraseSector(uint32_t block, uint32_t sector)
{
    const uint32_t &page_size = flash_device_.get_page_size(),
                   number_of_pages = flash_device_.get_number_of_pages(),
                   number_of_sectors = flash_device_.get_number_of_sectors();
    if (block >= flash_device_.get_number_of_blocks() || sector >= number_of_sectors)
    {
        return;
    }
    else
    {
        flash_device_.flash_sector_erase((page_size * number_of_pages * number_of_sectors * block) + (page_size * number_of_pages * sector));
    }
}

uint32_t MemoryManager::ValidatePage() const
{
    return 0;
}

uint32_t MemoryManager::ValidateSector() const
{
    return 0;
}

uint32_t MemoryManager::ValidateBlock() const
{
    return 0;
}
