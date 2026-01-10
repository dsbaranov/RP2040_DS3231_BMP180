#include "bmp180/bmp180.h"
#include "ds3231/ds3231.h"
#include "hardware/i2c.h"
#include "i2c/i2c_entity.h"
#include "pico/stdlib.h"
#include "ssd1315/ssd1315.h"
#include "ssd1315/ssd1315_example.h"
#include <cstring>
#include <iomanip>
#include <iostream>
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
    SSD1315::SSD1315 ssd1315(i2c.get(), SSD1315::domain::DisplaySizeType::w128h64);
    example::SSD1315 example_display(i2c.get());
    gpio_set_dir(LED_PIN, GPIO_OUT);
    gpio_put(LED_PIN, true);
    sleep_ms(500);
    gpio_put(LED_PIN, false);

    // ds3231.SetDateTimeBlock(DS3231::domain::DateTime{.seconds = 0,
    //                                                      .minutes = 50,
    //                                                      .hours = 14,
    //                                                      .dow = 4,
    //                                                      .day = 1,
    //                                                      .month = 1,
    //                                                      .year = 26,
    //                                                      .is_meridial = 0,
    //                                                      .is_pm = 0,
    //                                                      .age = 20});

    ds3231.Init();
    bmp180.GetCoefficients();
    bmp180.Init();

    example_display.init();
    example_display.drawString(0, 16, "Hello");
    example_display.display();

    printf("size of size_t - %i\n", sizeof(size_t));

    while (true)
    {
        bmp180.ReadData();
        auto datetime_f = ds3231.GetDateTime().AsFormatted();
        std::cout << datetime_f.day.c_str() << '.' << datetime_f.month.c_str() << '.' << datetime_f.year.c_str() << ' '
                  << datetime_f.hours.c_str() << ':' << datetime_f.minutes.c_str() << ':' << datetime_f.seconds.c_str()
                  << ' ' << std::setw(5) << std::setprecision(3) << bmp180.temperature() << "C " << std::setprecision(4)
                  << bmp180.pressure() << "mm" << std::endl;
        sleep_ms(1000);
    }
}
