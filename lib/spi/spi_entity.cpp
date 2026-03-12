#include "spi_entity.h"

SPI::SPI(spi_inst_t *spi, uint8_t rx, uint8_t tx, uint8_t sck) : spi_(spi)
{
    init(spi, rx, tx, sck);
}

void SPI::init(spi_inst_t *spi, uint8_t rx, uint8_t tx, uint8_t sck, uint32_t baudrate)
{
    gpio_set_function(rx, GPIO_FUNC_SPI);
    gpio_set_function(tx, GPIO_FUNC_SPI);
    gpio_set_function(sck, GPIO_FUNC_SPI);
    spi_init(spi, baudrate);
}

const spi_inst_t *SPI::get()
{
    return spi_;
}
