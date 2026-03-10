#pragma once
#include <cstdint>

namespace AHT10::REGISTERS
{
// Адресс устройства на шине I2C
static const uint8_t ADDR = 0x38;

// Флаги
static const uint8_t CMD_CTRL = 0xE1;

static const uint8_t CMD_MEASURE = 0xAC;

static const uint8_t MEASURE_CMD_HSB = 0x33;
static const uint8_t MEASURE_CMD_LSB = 0x00;

static const uint8_t CMD_RESET = 0xBA;
};