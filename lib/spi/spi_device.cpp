#include "spi_device.h"

SPIDevice::SPIDevice(const spi_inst_t *spi, uint8_t cs) : spi_(spi), cs_(cs)
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
