#pragma once

#include <cstdint>
// Наложение маски на старший полубайт
uint8_t byte_mask_msn(uint8_t value);
// Наложение маски на младший полубайт
uint8_t byte_mask_lsn(uint8_t value);
// Преобразование значения байта из десятичного в бинарно-десятичный
uint8_t byte_dec_to_bindec(uint8_t value);
// Преобразование значения байта из бинарно-десятичного в десятичный
uint8_t byte_bindec_to_dec(uint8_t value);