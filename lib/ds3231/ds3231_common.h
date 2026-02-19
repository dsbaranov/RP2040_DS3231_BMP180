#pragma once

#include <cstdint>
#include <string>
namespace DS3231::common
{
// Наложение маски на старший полубайт
uint8_t ByteMaskMsn(uint8_t value);
// Наложение маски на младший полубайт
uint8_t ByteMaskLsn(uint8_t value);
// Преобразование значения байта из десятичного в бинарно-десятичный
uint8_t ByteDecToBinDec(uint8_t value);
// Преобразование значения байта из бинарно-десятичного в десятичный
uint8_t ByteBinDecToDec(uint8_t value);
std::string FormatDecWithLeadingZero(uint8_t value, uint8_t width);
std::string FormatDecWithLeadingZero(uint8_t value);
} // namespace DS3231::common
