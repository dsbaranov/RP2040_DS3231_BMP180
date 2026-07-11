#include "crc8/crc8.h"

uint8_t crc8(const uint8_t *data, uint8_t len)
{
    uint8_t crc = 0x00;
    while (len--)
    {
        crc = crc8_table[crc ^ *data++];
    }
    return crc;
}