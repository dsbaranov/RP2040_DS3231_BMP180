#include "common.h"

// Наложение маски на старший полубайт
uint8_t byte_mask_msn(uint8_t value)
{
    return value & 0xF0;
}

// Наложение маски на младший полубайт
uint8_t byte_mask_lsn(uint8_t value)
{
    return value & 0x0F;
}

// Преобразование значения байта из десятичного в бинарно-десятичный
uint8_t byte_dec_to_bindec(uint8_t value)
{
    return (((value / 10u) << 4u) & 0xF0) | (value % 10u);
}

// Преобразование значения байта из бинарно-десятичного в десятичный
uint8_t byte_bindec_to_dec(uint8_t value)
{
    return (byte_mask_lsn(value >> 4) * 10) + byte_mask_lsn(value);
}