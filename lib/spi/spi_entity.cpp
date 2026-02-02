#include "spi_entity.h"

SPI::SPI(spi_inst_t *spi, uint8_t rx, uint8_t tx, uint8_t sck, uint8_t cs) : spi_(spi), cs_(cs)
{
    init(spi, rx, tx, sck, cs);
}

void SPI::init(spi_inst_t *spi, uint8_t rx, uint8_t tx, uint8_t sck, uint8_t cs)
{
    gpio_set_function(rx, GPIO_FUNC_SPI);
    gpio_set_function(tx, GPIO_FUNC_SPI);
    gpio_set_function(sck, GPIO_FUNC_SPI);
    spi_init(spi, BAUDRATE);
    gpio_init(cs);
    gpio_set_dir(cs, GPIO_OUT);
    gpio_put(cs, 1);
}

spi_inst_t *SPI::get()
{
    return spi_;
}
