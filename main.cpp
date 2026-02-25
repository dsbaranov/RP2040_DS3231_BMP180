#include "bmp180/bmp180.h"
#include "ds3231/ds3231.h"
#include "hardware/i2c.h"
#include "i2c/i2c_entity.h"
#include "pico/stdlib.h"
#include "spi/spi_entity.h"
#include "ssd1315/ssd1315.h"

#include <cmath>

// #include "ssd1315/ssd1315_example.h"
#include <cstddef>
#include <cstring>
#include <deque>
#include <iomanip>
#include <iostream>

// I2C defines
// This example will use I2C0 on GPIO8 (SDA) and GPIO9 (SCL) running at 400KHz.
// Pins can be changed, see the GPIO function select table in the datasheet for information on GPIO assignments
#define I2C_PORT i2c0
#define I2C_SDA 8
#define I2C_SCL 9
#define LED_PIN 25

static const uint8_t max_graph_x = 60;
static const uint8_t max_graph_y = 54;

uint8_t A2F_c = 0;

std::vector<double> graph;
uint8_t graph_counter = 0;

int main()
{
    stdio_init_all();
    I2C i2c(I2C_PORT, I2C_SCL, I2C_SDA);
    DS3231::DS3231 ds3231(i2c.get());
    BMP180::BMP180 bmp180(i2c.get());
    SSD1315::SSD1315 ssd1315(i2c.get(), SSD1315::domain::DisplaySizeType::w128h64);
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);
    gpio_put(LED_PIN, true);
    sleep_ms(500);
    gpio_put(LED_PIN, false);
    sleep_ms(500);

    // ds3231.SetDateTimeBlock(DS3231::domain::IDateTimeDetailed{0, 19, 0, 0, 9, 3, 25, 2, 26, 20});

    ds3231.init();
    ds3231.readControls();
    ds3231.readState();
    ds3231.State.A1F = ds3231.State.A2F = 0;
    ds3231.setState();
    ds3231.setAlarm(DS3231::domain::IAlarm2{25, 0, 0, 0, 0, 0, 0, 1, 1, 1});
    ds3231.Controls.INTCN = ds3231.Controls.A1IE = ds3231.Controls.A2IE = 1;
    ds3231.Controls.BBSQW = 0;
    ds3231.setControls();

    bmp180.init();
    ssd1315.init();
    ssd1315.clear();
    std::stringstream buf_ss("");
    graph.reserve(max_graph_x);
    uint8_t y0 = 63u;

    while (true)
    {
        auto datetime = ds3231.getDateTime();
        auto datetime_f = datetime.AsFormatted();
        ds3231.readState();
        bmp180.ReadData(false);
        if (ds3231.State.A2F == 1)
        {
            A2F_c++;
            ds3231.State.A2F = 0;
            ds3231.setState();
            bmp180.ReadData(true);
            if (datetime.minutes % 4 == 0)
            {
                if (graph.size() < max_graph_x)
                {
                    graph.push_back(bmp180.pressure());
                }
                else
                {
                    graph[graph_counter++] = bmp180.pressure();
                    if (graph_counter >= max_graph_x)
                    {
                        graph_counter = 0;
                    }
                }
            }
        }
        ssd1315.clearRect();
        buf_ss << std::setw(4) << std::setprecision(3) << bmp180.temperature();
        ssd1315.setCursor(0, 0)
            .setString(datetime_f.day)
            .setChar('.')
            .setString(datetime_f.month)
            .setChar('.')
            .setString(datetime_f.year)
            .setCursor(0, 8)
            .setString(datetime_f.hours)
            .setChar(':')
            .setString(datetime_f.minutes)
            .setChar(':')
            .setString(datetime_f.seconds)
            .setCursor(92, 8)
            .setString(buf_ss.str())
            .setDegree()
            .setChar('C');
        buf_ss.str("");
        buf_ss << "A2:" << (int)ds3231.State.A2F << " " << (int)A2F_c;
        ssd1315.setCursor(0, 16).setString(buf_ss.str());

        if (graph.size() > 0)
        {
            double pressure_min = bmp180.min();
            double pressure_max = bmp180.max();

            buf_ss.str("");
            buf_ss << std::setprecision(4) << pressure_max;
            ssd1315.setCursor(0, 40).setString(buf_ss.str());
            buf_ss.str("");
            buf_ss << std::setprecision(4) << pressure_min;
            ssd1315.setCursor(0, 56).setString(buf_ss.str());

            buf_ss.str("");
            buf_ss << std::setprecision(4) << bmp180.pressure();
            double graph_ratio = (pressure_max - pressure_min) / 24.;
            if (graph.size() < max_graph_x)
            {
                for (uint8_t counter = 0; counter < graph.size(); counter++)
                {
                    uint8_t x = 31u + counter;
                    uint8_t y = 63u - (graph.at(counter) - pressure_min) / graph_ratio;
                    if (y == 0)
                        break;
                    uint8_t y_from = std::max(y0, y);
                    uint8_t y_to = std::min(y0, y);
                    if (counter == graph.size() - 1)
                        ssd1315.setCursor(x + 1, y0 <= 55 ? y0 : 55u)
                            .setString("     ")
                            .setCursor(x + 2, y <= 55 ? y : 55u)
                            .setString(buf_ss.str());
                    for (; y_from >= y_to; --y_from)
                    {
                        ssd1315.setPixel(x, y_from, 1u);
                    }
                    y0 = y;
                }
            }
            else
            {
                uint8_t abs_counter = 0;
                ssd1315.setCursor(97, y0).setString("     ");
                for (uint8_t counter(graph_counter); counter < graph.size(); counter++)
                {
                    uint8_t x = 31u + abs_counter++;
                    uint8_t y = 63u - (graph.at(counter) - pressure_min) / graph_ratio;
                    if (y == 0)
                        break;
                    uint8_t y_from = (int)std::max(y0, y);
                    uint8_t y_to = (int)std::min(y0, y);
                    for (; y_from >= y_to; --y_from)
                    {
                        ssd1315.setPixel(x, y_from, 1u);
                    }
                    y0 = y;
                }
                for (uint8_t counter(0); counter < graph_counter; counter++)
                {
                    uint8_t x = 31u + abs_counter++;
                    uint8_t y = 63u - (graph.at(counter) - pressure_min) / graph_ratio;
                    if (y == 0)
                        break;
                    uint8_t y_from = (int)std::max(y0, y);
                    uint8_t y_to = (int)std::min(y0, y);
                    for (; y_from >= y_to; --y_from)
                    {
                        ssd1315.setPixel(x, y_from, 1u);
                    }
                    y0 = y;
                }
                ssd1315.setCursor(95, y0 <= 55 ? y0 : 55u).setString(buf_ss.str());
            }
        }

        ssd1315.draw();
        buf_ss.str("");
        sleep_ms(1000);
    }
}
