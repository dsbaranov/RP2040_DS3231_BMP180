#pragma once

#include <cstdint>

namespace DS3231::REGISTERS
{
/* АДРЕС УСТРОЙСТВА */
static const uint8_t ADDR = 0x68;

/* РЕГИСТРЫ УСТРОЙСТВА */
/* ДАННЫЕ */
static const uint8_t SECOND = 0x00;
static const uint8_t MINUTE = 0x01;
static const uint8_t HOUR = 0x02;
static const uint8_t DOW = 0x03;
static const uint8_t DAY = 0x04;
static const uint8_t MONTH = 0x05;
static const uint8_t YEAR = 0x06;
static const uint8_t NO_DATA = 0x07;

/* БУДИЛЬНИК */
static const uint8_t ALARM1_SEC = 0x07;
static const uint8_t ALARM1_MIN = 0x08;
static const uint8_t ALARM1_HOU = 0x09;
static const uint8_t ALARM1_DAY = 0x0A;
static const uint8_t ALARM1_DAT = 0x0A;

static const uint8_t ALARM2_MIN = 0x0B;
static const uint8_t ALARM2_HOU = 0x0C;
static const uint8_t ALARM2_DAY = 0x0D;
static const uint8_t ALARM2_DAT = 0x0D;

/* УПРАВЛЕНИЕ */
static const uint8_t CONTROL = 0x0E;
static const uint8_t CTL_STA = 0x0F;
static const uint8_t AGN_OFF = 0x10;
static const uint8_t MSB_TMP = 0x11;
static const uint8_t LSB_TMP = 0x12;

}; // namespace DS3231::REGISTERS
