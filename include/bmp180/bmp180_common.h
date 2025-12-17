#pragma once
#include <cstdint>

namespace BMP180::common
{

template <typename TYPE> inline TYPE UnifyBytes(uint8_t msb, uint8_t lsb)
{
    return ((static_cast<TYPE>(msb) << 8) & 0xFF00) | lsb;
}

inline int16_t Int16FromBytes(uint8_t msb, uint8_t lsb);

inline uint16_t Uint16FromBytes(uint8_t msb, uint8_t lsb);
} // namespace BMP180::common
