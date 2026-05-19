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
    : flash_device_ref_(flash_device),
      bmp180__ref_(bmp180),
      number_of_blocks_(flash_device.get_number_of_blocks()),
      number_of_sectors_(flash_device.get_number_of_sectors()),
      number_of_pages(flash_device.get_number_of_pages()),
      page_size(flash_device.get_page_size())
{
}
