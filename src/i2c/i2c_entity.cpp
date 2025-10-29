#include "i2c/i2c_entity.h"

I2C::I2C(i2c_inst_t *i2c, uint8_t scl_pin, uint8_t sda_pin)
{
    init(i2c, scl_pin, sda_pin);
}

i2c_inst_t *I2C::get()
{
    return i2c_;
}

void I2C::init(i2c_inst_t *i2c, uint8_t scl_pin, uint8_t sda_pin)
{
    i2c_ = i2c;
    i2c_init(i2c_, BAUDRATE);
    gpio_set_function(scl_pin, GPIO_FUNC_I2C);
    gpio_set_function(sda_pin, GPIO_FUNC_I2C);
    gpio_pull_up(scl_pin);
    gpio_pull_up(sda_pin);
}
// Тут снова был Магамек