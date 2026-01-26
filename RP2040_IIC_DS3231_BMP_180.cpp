#include "bmp180/bmp180.h"
#include "ds3231/ds3231.h"
#include "hardware/i2c.h"
#include "i2c/i2c_entity.h"
#include "pico/stdlib.h"
#include "ssd1315/ssd1315.h"

// #include "ssd1315/ssd1315_example.h"
#include <cstddef>
#include <cstring>
#include <iomanip>
#include <iostream>

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
    // example::SSD1315 example_display(i2c.get());
    gpio_set_dir(LED_PIN, GPIO_OUT);
    gpio_put(LED_PIN, true);
    sleep_ms(3000);
    gpio_put(LED_PIN, false);

    // ds3231.SetDateTimeBlock(DS3231::domain::DateTime{.seconds = 0,
    //                                                  .minutes = 52,
    //                                                  .hours = 14,
    //                                                  .dow = 1,
    //                                                  .day = 26,
    //                                                  .month = 1,
    //                                                  .year = 26,
    //                                                  .is_meridial = 0,
    //                                                  .is_pm = 0,
    //                                                  .age = 20});

    ds3231.Init();
    bmp180.GetCoefficients();
    bmp180.Init();

    ssd1315.init();
    // left top
    ssd1315.setPixel(0, 0, true);
    // right top
    ssd1315.setPixel(127, 0, true);
    // left bottom
    ssd1315.setPixel(0, 63, true);
    // right bottom
    ssd1315.setPixel(127, 63, true);
    // top center
    ssd1315.setPixel(64, 0, true);
    ssd1315.setPixel(65, 0, true);
    // center
    ssd1315.setPixel(64, 31, true);
    ssd1315.setPixel(65, 31, true);
    ssd1315.setPixel(64, 32, true);
    ssd1315.setPixel(65, 32, true);
    // bottom center
    ssd1315.setPixel(64, 63, true);
    ssd1315.setPixel(65, 63, true);
    // left center
    ssd1315.setPixel(0, 31, true);
    ssd1315.setPixel(0, 32, true);
    // right center
    ssd1315.setPixel(127, 31, true);
    ssd1315.setPixel(127, 32, true);
    ssd1315.render();
    sleep_ms(1000);
    ssd1315.clear();
    std::stringstream buf_ss("");
    while (true)
    {
        bmp180.ReadData();
        auto datetime_f = ds3231.GetDateTime().AsFormatted();
        std::cout << datetime_f.day.c_str() << '.' << datetime_f.month.c_str() << '.' << datetime_f.year.c_str() << ' '
                  << datetime_f.hours.c_str() << ':' << datetime_f.minutes.c_str() << ':' << datetime_f.seconds.c_str()
                  << ' ' << std::setprecision(3) << bmp180.temperature() << "C " << std::setprecision(4)
                  << bmp180.pressure() << "mm" << std::endl;

        buf_ss << std::setw(5) << std::setprecision(3) << bmp180.temperature();
        ssd1315.setCursor(0, 0)
            .setString(datetime_f.day)
            .setChar('.')
            .setString(datetime_f.month)
            .setChar('.')
            .setString(datetime_f.year)
            .setChar(' ')
            .setCursor(0, 8)
            .setString(datetime_f.hours)
            .setChar(':')
            .setString(datetime_f.minutes)
            .setChar(':')
            .setString(datetime_f.seconds)
            .setCursor(0, 16)
            .setString(buf_ss.str())
            .setDegree()
            .setChar('C')
            .setChar(' ');
        buf_ss.str("");
        buf_ss << bmp180.pressure() << "mm";
        ssd1315.setCursor(0, 24).setString(buf_ss.str());
        ssd1315.render();
        buf_ss.str("");
        sleep_ms(1000);
    }
}
