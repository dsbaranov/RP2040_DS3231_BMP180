#include "ds3231.h"
#include "hardware/i2c.h"
#include "iic.h"
#include "pico/stdlib.h"
#include <cstring>
#include <stdio.h>
// I2C defines
// This example will use I2C0 on GPIO8 (SDA) and GPIO9 (SCL) running at 400KHz.
// Pins can be changed, see the GPIO function select table in the datasheet for information on GPIO assignments
#define I2C_PORT i2c0
#define I2C_SDA 8
#define I2C_SCL 9
#define LED_PIN 25

uint8_t format_time(uint8_t value)
{
    return ((value >> 4) & 0x0F) * 10 + (value & 0x0F);
}

const char *byte_to_binary(int x)
{
    static char buffer[9]; // 8 bits + null terminator
    buffer[0] = '\0';

    int z;
    for (z = 128; z > 0; z >>= 1)
    {
        strcat(buffer, ((x & z) == z) ? "1" : "0");
    }
    return buffer;
}

int main()
{
    stdio_init_all();

    // I2C Initialisation. Using it at 400Khz.
    I2C i2c(I2C_PORT, I2C_SCL, I2C_SDA);
    DS3231::DS3231 ds3231(i2c.get());

    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);

    gpio_put(LED_PIN, true);
    sleep_ms(1000);
    gpio_put(LED_PIN, false);
    // For more examples of I2C use see https://github.com/raspberrypi/pico-examples/tree/master/i2c

    while (true)
    {
        ds3231.read_register(0x00, 1);
        uint8_t sec = format_time(ds3231.buffer()[1]);
        ds3231.read_register(0x01, 1);
        uint8_t min = format_time(ds3231.buffer()[1]);
        ds3231.read_register(0x03, 1);
        uint8_t hou = format_time(ds3231.buffer()[1]);
        printf("sec(0x00): %i min(0x01): %i hour(0x03): %i\n", sec, min, hou);
        sleep_ms(1000);
    }
}
