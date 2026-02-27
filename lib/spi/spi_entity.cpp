#include "spi_entity.h"

namespace spi
{

Spi::Spi(spi_inst_t *spi, uint8_t rx, uint8_t tx, uint8_t sck, uint8_t cs) : spi_(spi), cs_(cs)
{
    init(spi, rx, tx, sck, cs);
}

void Spi::init(spi_inst_t *spi, uint8_t rx, uint8_t tx, uint8_t sck, uint8_t cs, uint32_t baudrate)
{
    gpio_set_function(rx, GPIO_FUNC_SPI);
    gpio_set_function(tx, GPIO_FUNC_SPI);
    gpio_set_function(sck, GPIO_FUNC_SPI);
    spi_init(spi, baudrate);
    gpio_init(cs);
    gpio_set_dir(cs, GPIO_OUT);
    gpio_put(cs, 1);
}

void Spi::toggleCsPin(uint8_t cs_pin, uint8_t state)
{
    asm volatile("nop \n nop \n nop");
    gpio_put(cs_pin, state);
    asm volatile("nop \n nop \n nop");
}

void Spi::select()
{
    toggleCsPin(cs_, 0);
}

void Spi::deselect()
{
    toggleCsPin(cs_, 1);
}

const spi_inst_t *Spi::get()
{
    return spi_;
}
}; // namespace spi
