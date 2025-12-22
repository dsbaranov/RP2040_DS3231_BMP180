#pragma once

#include <cstdint>

namespace BMP180::REGISTERS
{
static const uint8_t ADDR = 0x77;

// Калибровочные коэффициенты

// Регистр 2 байт R
static const uint8_t AC1 = 0xAA;
// Регистр 2 байт R
static const uint8_t AC2 = 0xAC;
// Регистр 2 байт R
static const uint8_t AC3 = 0xAE;
// Регистр 2 байт R
static const uint8_t AC4 = 0xB0;
// Регистр 2 байт R
static const uint8_t AC5 = 0xB2;
// Регистр 2 байт R
static const uint8_t AC6 = 0xB4;
// Регистр 2 байт R
static const uint8_t B1 = 0xB6;
// Регистр 2 байт R
static const uint8_t B2 = 0xB8;
// Регистр 2 байт R
static const uint8_t MB = 0xBA;
// Регистр 2 байт R
static const uint8_t MC = 0xBC;
// Регистр 2 байт R
static const uint8_t MD = 0xBE;
// Регистр 1 байт R. Значение всегда 0x55(напр. для проверки связи)
static const uint8_t CHIP_ID = 0xD0;
/**
 * @brief Регистр 1 байт.Запись 0xB6 приводит к сбросу как при включении питания.
 */
static const uint8_t SOFT_RESET = 0xE0;
/**
 * @brief Регистр 1 байт R/W. Управление измерениями
 * @param OSS - режим точности : 7 6 биты
 * @param CSO - флаг состояния : 5 бит
 * @param CTR - биты управления : 3 2 1 0 биты
 */
static const uint8_t MEASUREMENT_CTRL = 0xF4;
// Регистр 1 байт R. Старший байт результата.
static const uint8_t OUT_MSB = 0xF6;
// Регистр 1 байт R. Младший байт результата.
static const uint8_t OUT_LSB = 0xF7;
// Регистр 1 байт R. Доп. биты младшего байта результата [7 6 5 4 3 Доп биты | 2 1 0 Нули].
static const uint8_t OUT_xLSB = 0xF8;
} // namespace BMP180::REGISTERS