#include "ds3231/ds3231.h"
#include "hardware/i2c.h"
#include "i2c/i2c_entity.h"
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

    // ds3231.set_hours_register(11, 0, 0)
    //     .set_minutes_register(3)
    //     .set_seconds_register(0)
    //     .set_dow_register(1)
    //     .set_day_register(28)
    //     .set_month_register(10)
    //     .set_year_register(2025);

    while (true)
    {
        auto datetime_f = ds3231.GetDateTime().AsFormatted();
        printf("%s.%s.%s %s:%s:%s\n", datetime_f.day.c_str(), datetime_f.month.c_str(), datetime_f.year.c_str(),
               datetime_f.hours.c_str(), datetime_f.minutes.c_str(), datetime_f.seconds.c_str());
        sleep_ms(1000);
    }
}
