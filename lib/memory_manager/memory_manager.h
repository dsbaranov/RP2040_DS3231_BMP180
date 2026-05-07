#pragma once
#include <iostream>
#include "spi/spi_flash_device.h"
class MemoryManager
{
private:
    FlashDevice &flash_device_;

public:
    MemoryManager(FlashDevice &flash_device) : flash_device_(flash_device)
    {
    }
};