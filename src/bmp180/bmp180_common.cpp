#include "bmp180/bmp180_common.h"

namespace BMP180::common
{
inline int16_t Int16FromBytes(uint8_t msb, uint8_t lsb)
{
    return UnifyBytes<int16_t>(msb, lsb);
}

inline uint16_t Uint16FromBytes(uint8_t msb, uint8_t lsb)
{
    return UnifyBytes<uint16_t>(msb, lsb);
}
} // namespace BMP180::common
