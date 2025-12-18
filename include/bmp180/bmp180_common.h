#pragma once
#include <cstdint>

namespace BMP180::common
{

template <typename TYPE> inline TYPE UnifyBytes(uint8_t msb, uint8_t lsb)
{
    return ((static_cast<TYPE>(msb) << 8) & 0xFF00) | lsb;
}

} // namespace BMP180::common
