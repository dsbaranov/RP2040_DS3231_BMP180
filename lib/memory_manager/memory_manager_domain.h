#pragma once
#include <cstdint>

struct MemoryDataChunk
{
    uint8_t age;
    uint8_t year;
    uint8_t month;
    uint8_t day;
    uint8_t hour;
    uint8_t minute;
    uint8_t pressure_to_max;
    uint16_t pressure;
    uint8_t pressure_to_min;
    uint16_t temperature;
    uint8_t humidity;
};
