#include "bmp180/bmp180.h"
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
    BMP180::BMP180 bmp180(i2c.get());

    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);

    gpio_put(LED_PIN, true);
    sleep_ms(1000);
    gpio_put(LED_PIN, false);

    //     ds3231.SetDateTimeBlock(DS3231::domain::DateTime{.seconds = 0,
    //                                                      .minutes = 28,
    //                                                      .hours = 13,
    //                                                      .dow = 3,
    //                                                      .day = 17,
    //                                                      .month = 12,
    //                                                      .year = 25,
    //                                                      .is_meridial = 0,
    //                                                      .is_pm = 0,
    //                                                      .age = 20});

    ds3231.ReadControls();
    printf("OLD : EOSC:%i BBSQW:%i CONV:%i RS1:%i RS2:%i INTCN:%i A2IE:%i A1IE:%i\n", ds3231.controls.EOSC,
           ds3231.controls.BBSQW, ds3231.controls.CONV, ds3231.controls.RS2, ds3231.controls.RS1, ds3231.controls.INTCN,
           ds3231.controls.A2IE, ds3231.controls.A1IE);
    ds3231.Init();
    ds3231.ReadControls();
    printf("NEW : EOSC:%i BBSQW:%i CONV:%i RS1:%i RS2:%i INTCN:%i A2IE:%i A1IE:%i\n", ds3231.controls.EOSC,
           ds3231.controls.BBSQW, ds3231.controls.CONV, ds3231.controls.RS2, ds3231.controls.RS1, ds3231.controls.INTCN,
           ds3231.controls.A2IE, ds3231.controls.A1IE);

    bmp180.GetCoefficients();

    while (true)
    {
        auto datetime_f = ds3231.GetDateTime().AsFormatted();
        printf("%s.%s.%s %s:%s:%s\n", datetime_f.day.c_str(), datetime_f.month.c_str(), datetime_f.year.c_str(),
               datetime_f.hours.c_str(), datetime_f.minutes.c_str(), datetime_f.seconds.c_str());
        bool present = bmp180.Ping();
        printf("bmp180 is %s\n", present ? "present" : "not present");
        sleep_ms(1000);
    }
}
