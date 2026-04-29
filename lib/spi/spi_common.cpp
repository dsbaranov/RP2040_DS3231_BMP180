#include "spi_common.h"
#include <utility>

uint8_t get_left_shifted_byte(uint32_t value, uint8_t shift)
{
    if (shift >= 32)
    {
        return 0;
    }
    return static_cast<uint8_t>((value >> shift) & 0xFF);
}

std::vector<uint8_t> form_cmd_buf(uint8_t cmd, uint32_t addr)
{
    std::vector<uint8_t> result(4);
    result.push_back(cmd);
    for (uint8_t counter = 2; counter > 0; counter--)
    {
        result.push_back(get_left_shifted_byte(addr, 8u * counter));
    }
    return result;
}