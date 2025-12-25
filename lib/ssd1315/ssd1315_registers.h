#pragma once

#include <cstdint>

namespace ssd1315::REGISTERS
{

// I2C Device address
static const uint8_t ADDR = 0x3C;

// Set the lower nibble of the column start address register for Page Addressing Mode using X[3:0] as data
// bits. The initial display line register is reset to 0000b after RESET.
static const uint8_t CMD_LCSA_PAM = 0x00;

// Set the higher nibble of the column start address
// register for Page Addressing Mode using X[2:0] as
// data bits. The initial display line register is reset to
// 0000b after RESET.
static const uint8_t CMD_HCSA_PAM = 0x10;

// A[1:0] = 00b, Horizontal Addressing Mode
// A[1:0] = 01b, Vertical Addressing Mode
// A[1:0] = 10b, Page Addressing Mode (RESET)
// A[1:0] = 11b, Invalid
static const uint8_t CMD_MEMO_ADR_MODE = 0x20;
enum class CMD_MEMO_ADR_MODES
{
    HORIZONTAL = 0,
    VERTICAL = 1,
    PAGE = 2
};

// Setup column start and end address
// A[6:0] : Column start address, range : 0-127d,
// (RESET=0d)
// B[6:0]: Column end address, range : 0-127d,
// (RESET =127d)
// Note
// (1) This command is only for horizontal or vertical
// addressing mode.
static const uint8_t CMD_COL_ADDRESS = 0x21;

// Setup page start and end address
// A[2:0] : Page start Address, range : 0-7d,
// (RESET = 0d)
// B[2:0] : Page end Address, range : 0-7d,
// (RESET = 7d)
// Note
// (1) This command is only for horizontal or vertical
// addressing mode
static const uint8_t CMD_PAGE_ADDRESS = 0x22;

// Set display RAM display start line register from 0-
// 63 using X5 X4X3X2X1X0.
// Display start line register is reset to 000000b
// during RESET.
static const uint8_t CMD_DISPLAY_START_LINE = 0x40;

// Double byte command to select one of the contrast
// steps. Contrast increases as the value increases.
// (RESET = 7Fh)
// A[7:0] valid range: 01h to FFh
static const uint8_t CMD_CONTRAST_CTRL = 0x81;

// A0h, X[0]=0b: column address 0 is mapped to
// SEG0 (RESET)
// A1h, X[0]=1b: column address 127 is mapped to
// SEG0
static const uint8_t CMD_SEGMENT_REMAP = 0xA0;

// A4h, X0=0b: Resume to RAM content display
//  (RESET)
//  Output follows RAM content
// A5h, X0=1b: Entire display ON
//  Output ignores RAM content
static const uint8_t CMD_DISPLAY_ON = 0xA4;

// A6h, X[0]=0b: Normal display (RESET)
//  0 in RAM: OFF in display panel
//  1 in RAM: ON in display panel
// A7h, X[0]=1b: Inverse display
//  0 in RAM: ON in display panel
//  1 in RAM: OFF in display panel
static const uint8_t CMD_INVERSE_DISPLAY = 0xA6;

// Set MUX ratio to N+1 MUX
// N=A[5:0] : from 16MUX to 64MUX.
// RESET = 111111b (i.e. 63d, 64MUX)
// A[5:0] from 0 to 14 are invalid entry
static const uint8_t CMD_MULTIPLEX_RATIO = 0xA8;

} // namespace ssd1315::REGISTERS