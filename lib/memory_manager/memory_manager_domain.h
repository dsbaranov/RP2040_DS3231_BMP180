#pragma once
#include <cstdint>

struct DataChunk
{
    uint16_t pressure_max;
    uint16_t pressure;
    uint16_t pressure_min;
    uint16_t temperature;
    uint16_t year;
    uint8_t month;
    uint8_t day;
    uint8_t hour;
    uint8_t minute;
    uint8_t humidity;
};

struct FlashDataChunk
{
    uint16_t pressure_max;
    uint16_t pressure;
    uint16_t pressure_min;
    uint16_t temperature;
    uint16_t year;
    uint8_t month;
    uint8_t day;
    uint8_t hour;
    uint8_t minute;
    uint8_t humidity;
    uint8_t crc;
};
