#pragma once
#include <iostream>
#include "spi/spi_flash_device.h"
#include "bmp180/bmp180.h"

class MemoryManager
{
private:
    FlashDevice &flash_device_ref_;
    BMP180::BMP180 &bmp180__ref_;

    void set_max_pressure_bmp180(double value);
    void set_min_pressure_bmp180(double value);

public:
    MemoryManager(FlashDevice &flash_device, BMP180::BMP180 &bmp180) : flash_device_ref_(flash_device), bmp180__ref_(bmp180)
    {
    }
};