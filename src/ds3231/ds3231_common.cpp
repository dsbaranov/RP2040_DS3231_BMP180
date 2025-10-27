#include "ds3231/ds3231_common.h"

namespace DS3231::common
{
// Наложение маски на старший полубайт
uint8_t ByteMaskMsn(uint8_t value)
{
    return value & 0xF0;
}

// Наложение маски на младший полубайт
uint8_t ByteMaskLsn(uint8_t value)
{
    return value & 0x0F;
}

// Преобразование значения байта из десятичного в бинарно-десятичный
uint8_t ByteDecToBinDec(uint8_t value)
{
    if (value == 0)
    {
        return 0;
    }
    return (((value / 10u) << 4u) & 0xF0) | (value % 10u);
}

// Преобразование значения байта из бинарно-десятичного в десятичный
uint8_t ByteBinDecToDec(uint8_t value)
{
    return (ByteMaskLsn(value >> 4) * 10) + ByteMaskLsn(value);
}

std::string FormatDecWithLeadingZero(uint8_t value, uint8_t width = 2u)
{
    if (width == 0)
    {
        return "";
    }
    std::string result(width, '0');
    uint8_t cnt = 1;
    do
    {
        uint8_t symbol = value % 10u;
        result[result.size() - cnt++] = symbol + '0';
        value /= 10u;
    } while (value > 0);
    return result;
}
std::string FormatDecWithLeadingZero(uint8_t value)
{
    return FormatDecWithLeadingZero(value, 2u);
}
} // namespace DS3231::common
