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

    // ds3231.SetHours(22, 0, 0).SetMinutes(31).SetSeconds(0).SetDow(1).SetDay(28).SetMonth(10).SetYear(2025);
    ds3231.SetDateTimeBlock(DS3231::domain::DateTime{.seconds = 0,
                                                     .minutes = 55,
                                                     .hours = 23,
                                                     .dow = 1,
                                                     .day = 28,
                                                     .month = 10,
                                                     .year = 25,
                                                     .is_meridial = 0,
                                                     .is_pm = 0,
                                                     .age = 20});

    while (true)
    {
        auto datetime_f = ds3231.GetDateTime().AsFormatted();
        printf("%s.%s.%s %s:%s:%s\n", datetime_f.day.c_str(), datetime_f.month.c_str(), datetime_f.year.c_str(),
               datetime_f.hours.c_str(), datetime_f.minutes.c_str(), datetime_f.seconds.c_str());
        sleep_ms(1000);
    }
}
