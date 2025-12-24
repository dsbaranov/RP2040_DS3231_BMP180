#pragma once

#include <cstdint>

namespace ssd1315::REGISTERS
{

static const uint8_t ADDR = 0x3C;
static const uint8_t SET_MEM_MODE = 0x20;
static const uint8_t SET_COLUMN_ADDR = 0x21;
static const uint8_t SET_PAGE_ADDR = 0x22;
static const uint8_t SET_HORIZONTAL_SCROLL = 0x26;
static const uint8_t SET_SCROLL = 0x2E;
static const uint8_t SET_DISPLAY_START_LINE = 0x40;
static const uint8_t SET_CONTRAST = 0x81;
static const uint8_t SET_CHARGE_PUMP = 0x8D;
static const uint8_t SET_SEG_REMAP = 0xA0;
static const uint8_t SET_ENTIRE_ON = 0xA4;
static const uint8_t SET_ALL_ON = 0xA5;
static const uint8_t SET_NORM_DISP = 0xA6;
static const uint8_t SET_INV_DISP = 0xA7;
static const uint8_t SET_MUX_RATIO = 0xA8;
static const uint8_t SET_DISP = 0xAE;
static const uint8_t SET_COM_OUT_DIR = 0xC0;
static const uint8_t SET_COM_OUT_DIR_FLIP = 0xC0;
static const uint8_t SET_DISP_OFFSET = 0xD3;
static const uint8_t SET_DISP_CLK_DIV = 0xD5;
static const uint8_t SET_PRECHARGE = 0xD9;
static const uint8_t SET_COM_PIN_CFG = 0xDA;
static const uint8_t SET_VCOM_DESEL = 0xDB;
static const uint8_t WRITE_MODE = 0xFE;
static const uint8_t READ_MODE = 0xFF;

} // namespace ssd1315::REGISTERS