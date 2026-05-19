#include "aht10/aht10.h"
#include "bmp180/bmp180.h"
#include "ds3231/ds3231.h"
#include "hardware/i2c.h"
#include "i2c/i2c_entity.h"
#include "pico/stdlib.h"
#include "spi/spi_entity.h"
#include "w25q32bv/w25q32bv.h"
#include "ssd1315/ssd1315.h"
#include "memory_manager/memory_manager_domain.h"

#include <cmath>

#include <cstddef>
#include <cstring>
#include <deque>
#include <iomanip>
#include <iostream>

// I2C defines
// This example will use I2C0 on GPIO8 (SDA) and GPIO9 (SCL) running at 400KHz.
// Pins can be changed, see the GPIO function select table in the datasheet for
// information on GPIO assignments
#define I2C_INST i2c0
#define I2C_SDA 8
#define I2C_SCL 9
#define LED_PIN 25

#define SPI_INST spi0
#define SPI_RX 16
#define SPI_TX 19
#define SPI_SCK 18
#define SPI_CS 17

static const uint8_t max_graph_x = 60;

uint8_t A2F_c = 0;

std::vector<double> graph;
uint8_t graph_counter = 0;

int main()
{
    stdio_init_all();
    SPI spi_i(SPI_INST, SPI_RX, SPI_TX, SPI_SCK);

    I2C i2c_i(I2C_INST, I2C_SCL, I2C_SDA);
    DS3231::DS3231 ds3231(i2c_i.get());
    BMP180::BMP180 bmp180(i2c_i.get());
    SSD1315::SSD1315 ssd1315(i2c_i.get(), SSD1315::domain::DisplaySizeType::w128h64);
    AHT10::AHT10 aht10(i2c_i.get());
    W25Q32BV w25q32bv(spi_i.get(), SPI_CS);
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);
    gpio_put(LED_PIN, true);
    sleep_ms(500);
    gpio_put(LED_PIN, false);
    sleep_ms(500);

    // ds3231.setDateTimeBlock({0, 33, 0, 0, 22, 19, 2, 0, 5, 26, 20});

    ds3231.init();
    bmp180.init();
    ssd1315.init();
    ssd1315.clear();
    // {
    //     auto flash_datetime = ds3231.getDateTime();
    //     std::vector<uint8_t> wbuf{flash_datetime.hours, flash_datetime.minutes, flash_datetime.seconds, flash_datetime.dow};
    //     std::cout << "erasing sector 0x00...";
    //     w25q32bv.flash_sector_erase(0x00);
    //     std::cout << "done." << std::endl;
    //     std::cout << "writing pages... ";
    //     for (uint8_t val : wbuf)
    //     {
    //         std::cout << (int)val << " ";
    //     }
    //     w25q32bv.flash_page_program(0x00, wbuf.data());
    //     std::cout << "done." << std::endl;
    //     std::cout << "reading pages... ";
    //     std::vector<uint8_t> rbuf(4);
    //     w25q32bv.flash_read(0x00, rbuf.data(), 4);
    //     for (uint8_t val : rbuf)
    //     {
    //         std::cout << (int)val << " ";
    //     }
    //     std::cout << "done." << std::endl;
    // }
    std::stringstream buf_ss("");
    graph.reserve(max_graph_x);
    uint8_t y0 = 63u;

    std::cout << "size of MemoryDataChunk : " << sizeof(MemoryDataChunk) << std::endl;
    bmp180.ReadData(true);
    while (true)
    {
        auto datetime = ds3231.getDateTime();
        auto datetime_f = datetime.AsFormatted();
        ds3231.readState();
        aht10.readData();
        if (ds3231.State.A2F == 1)
        {
            A2F_c++;
            ds3231.State.A2F = 0;
            ds3231.setState();
            bmp180.ReadData(true);
            // if (datetime.minutes % 4 == 0)
            // {
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
            // }
        }
        ssd1315.clearRect();
        buf_ss << std::setw(4) << std::setprecision(3) << aht10.temperature();
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
            .setCursor(92, 0)
            .setString(buf_ss.str())
            .setDegree()
            .setChar('C');
        buf_ss.str("");
        buf_ss << (int)aht10.humidity() << "%";
        ssd1315.setCursor(92, 8).setString(buf_ss.str());
        uint16_t pressure_min = bmp180.getMin();
        uint16_t pressure_max = bmp180.getMax();
        buf_ss.str("");
        buf_ss << pressure_max;
        ssd1315.setCursor(0, 18).setString(buf_ss.str());
        buf_ss.str("");
        buf_ss << pressure_min;
        ssd1315.setCursor(0, 56).setString(buf_ss.str());

        buf_ss.str("");
        buf_ss << bmp180.pressure();
        double graph_ratio = (pressure_max - pressure_min) / 44.;
        if (graph.size() > 0 && graph.size() < max_graph_x)
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

        ssd1315.draw();
        buf_ss.str("");
        sleep_ms(1000);
    }
}
