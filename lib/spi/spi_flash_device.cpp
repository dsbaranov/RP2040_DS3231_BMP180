#include "spi_flash_device.h"

spi_inst_t *FlashDevice::getSpiPtr() const
{
    return spi_;
}

void FlashDevice::select()
{
    SPIDevice::select();
}

void FlashDevice::deselect()
{
    SPIDevice::deselect();
}
