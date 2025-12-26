#pragma once

#include <cstdint>

namespace ssd1315::REGISTERS
{

// I2C Device address
inline static const uint8_t ADDR = 0x3C;

// Set the lower nibble of the column start address register for Page Addressing Mode using X[3:0] as data
// bits. The initial display line register is reset to 0000b after RESET.
// Mask : [ 0 0 0 0 X3 X2 X1 X0 ]
inline static const uint8_t CMD_LCSA_PAM = 0x00;

// Set the higher nibble of the column start address
// register for Page Addressing Mode using X[2:0] as
// data bits. The initial display line register is reset to
// 0000b after RESET.
// Mask : [ 0 0 0 1 0 X2 X1 X0 ]
inline static const uint8_t CMD_HCSA_PAM = 0x10;

// A[1:0] = 00b, Horizontal Addressing Mode
// A[1:0] = 01b, Vertical Addressing Mode
// A[1:0] = 10b, Page Addressing Mode (RESET)
// A[1:0] = 11b, Invalid
// Mask : [ 0 0 1 0 0 0 0 0 ][ 0 0 0 0 0 0 A1 A0 ]
inline static const uint8_t CMD_MEMO_ADR_MODE = 0x20;
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
// Mask : [ 0 0 1 0 0 0 0 1 ][ 0 A6 A5 A4 A3 A2 A1 A0 ][ 0 B6 B5 B4 B3 B2 B1 B0 ]
static const uint8_t CMD_COL_ADDRESS = 0x21;

// Setup page start and end address
// A[2:0] : Page start Address, range : 0-7d,
// (RESET = 0d)
// B[2:0] : Page end Address, range : 0-7d,
// (RESET = 7d)
// Note
// (1) This command is only for horizontal or vertical
// addressing mode
// Mask : [ 0 0 1 0 0 0 1 0 ][ 0 0 0 0 0 A2 A1 A0 ][ 0 0 0 0 0 B2 B1 B0 ]
static const uint8_t CMD_PAGE_ADDRESS = 0x22;

// Set display RAM display start line register from 0-
// 63 using X5 X4X3X2X1X0.
// Display start line register is reset to 000000b
// during RESET.
// Mask : [ 0 1 X5 X4 X3 X2 X1 X0 ]
static const uint8_t CMD_DISPLAY_START_LINE = 0x40;

// Double byte command to select one of the contrast
// steps. Contrast increases as the value increases.
// (RESET = 7Fh)
// A[7:0] valid range: 01h to FFh
// Mask : [ 1 0 0 0 0 0 0 1 ][ A7 A6 A5 A4 A3 A2 A1 A0 ]
static const uint8_t CMD_CONTRAST_CTRL = 0x81;

// A0h, X[0]=0b: column address 0 is mapped to
// SEG0 (RESET)
// A1h, X[0]=1b: column address 127 is mapped to
// SEG0
// Mask : [ 1 0 1 0 0 0 0 X0 ]
static const uint8_t CMD_SEGMENT_REMAP = 0xA0;

//  A4h, X0=0b: Resume to RAM content display
//  (RESET)
//  Output follows RAM content
//  A5h, X0=1b: Entire display ON
//  Output ignores RAM content
//  Mask : [ 1 0 1 0 0 1 0 X0 ]
static const uint8_t CMD_ENTIRE_DISPLAY_ON = 0xA4;

// A6h, X[0]=0b: Normal display (RESET)
//  0 in RAM: OFF in display panel
//  1 in RAM: ON in display panel
// A7h, X[0]=1b: Inverse display
//  0 in RAM: ON in display panel
//  1 in RAM: OFF in display panel
// Mask : [ 1 0 1 0 0 1 1 X0 ]
static const uint8_t CMD_INVERSE_DISPLAY_NORMAL = 0xA6;

// Set MUX ratio to N+1 MUX
// N=A[5:0] : from 16MUX to 64MUX.
// RESET = 111111b (i.e. 63d, 64MUX)
// A[5:0] from 0 to 14 are invalid entry
// Mask : [ 1 0 1 0 1 0 0 0 ][ 0 0 A5 A4 A3 A2 A1 A0 ]
static const uint8_t CMD_MULTIPLEX_RATIO = 0xA8;

// AEh, X[0]=0b: Display OFF (sleep mode)
// (RESET)
// AFh X[0]=1b: Display ON in normal mode
// Mask : [ 1 0 1 0 1 1 1 X0 ]
static const uint8_t CMD_DISPLAY = 0xAE;

// Set GDDRAM Page Start Address
// PAGE0~PAGE7 for Page Addressing Mode
// using X[2:0].
// Note
// (1) This command is only for page addressing mode
// Mask : [ 1 0 1 1 0 X2 X1 X0]
static const uint8_t CMD_PAGE_START_ADDRESS = 0xB0;

// C0h, X[3]=0b: normal mode (RESET) Scan from
// COM0 to COM[N –1]
// C8h, X[3]=1b: remapped mode. Scan from
// COM[N-1] to COM0
// Where N is the Multiplex ratio.
// Mask : [ 1 1 0 0 X3 0 0 0 ]
static const uint8_t CMD_COM_OUTPUT_SCAN_DIR = 0xC0;

// Set vertical shift by COM from 0d~63d.
// The value is reset to 00h after RESET.
// Mask : [ 1 1 0 1 0 0 1 1 ][ 0 0 A5 A4 A3 A2 A1 A0 ]
static const uint8_t CMD_DISPLAY_OFFSET = 0xD3;

// A[3:0] : Define the divide ratio (D) of the display
// clocks (DCLK):
// Divide ratio= A[3:0] + 1, RESET is 0000b
// (divide ratio = 1)
//
// A[7:4] : Set the Oscillator Frequency, FOSC.
// Oscillator Frequency increases with the
// value of A[7:4] and vice versa. RESET
// is 1000b.
// Range: 0000b~1111b. Frequency increases
// as setting value increases.
// Mask : [ 1 1 0 1 0 1 0 1 ][ A7 A6 A5 A4 A3 A2 A1 A0 ]
static const uint8_t CMD_DISPLAY_CLOCK_DIVIDE_RATIO = 0xD5;

// A[3:0] : Phase 1 period of up to 30 DCLK
//     (i.e. 2, 4, 6, …30)
//     Clocks 0 is invalid entry (RESET=2h)
// A[7:4] : Phase 2 period of up to 30 DCLK
//     (i.e. 2, 4, 6, …30)
//     Clocks 0 is invalid entry (RESET=2h )
// Mask : [ 1 1 0 1 1 0 0 1 ][ A7 A6 A5 A4 A3 A2 A1 A0 ]
static const uint8_t CMD_PRECHARGE_PERIOD = 0xD9;

// A[4]=0b, Sequential COM pin configuration
// A[4]=1b (RESET), Alternative COM pin Configuration

// A[5]=0b (RESET), Disable COM Left/Right remap
// A[5]=1b, Enable COM Left/Right remap
// Mask : [ 1 1 0 1 1 0 1 0 ][ 0 0 A5 A4 0 0 1 0 ]
static const uint8_t CMD_COM_PINS_HW_CONF = 0xDA;

// Set COM select voltage level.
// A[5:4] Hex   V COMH deselect level
// 00b    00h   ~ 0.65 x VCC
// 01b    10h   ~ 0.71 x VCC
// 10b    20h   ~ 0.77 x VCC (RESET)
// 11b    30h   ~ 0.83 x VCC
// Mask : [ 1 1 0 1 1 0 1 1 ][ 0 0 A5 A4 0 0 0 0 ]
static const uint8_t CMD_VCOMH_SELECT_LEVEL = 0xDB;

// Command for no operation
// Mask : [ 1 1 1 0 0 0 1 1 ]
static const uint8_t CMD_NO_OP = 0xE3;

/*
Enable / Disable internal charge pump:
A[2] = 0b, Disable charge pump (RESET)
A[2] = 1b, Enable charge pump during display on

A[7]    A[0]    Hex code    Charge Pump Mode
0b      0b      14h         7.5V (RESET)
1b      0b      94h         8.5V
1b      1b      95h         9.0V

Note
(1) The Charge Pump must be enabled by the
following command sequence:
8Dh ;
Charge Pump Setting 14h / 94h / 95h ;
Enable Charge Pump AFh;
Display ON
Mask : [ 1 0 0 0 1 1 0 1 ][ A7 0 0 1 0 A2 0 A0 ]
*/
static const uint8_t CMD_CHARGE_PUMP = 0x8D;

/*
26h, X[0]=0, Right Horizontal Scroll
27h, X[0]=1, Left Horizontal Scroll
(Horizontal scroll by 1 column)
A[7:0] : Dummy byte (Set as 00h)
B[2:0] : Define start page address
000b – PAGE0        011b – PAGE3        10b – PAGE6
001b – PAGE1        100b – PAGE4        11b – PAGE7
010b – PAGE2        101b – PAGE5
C[2:0] : Set time interval between each scroll step in
terms of frame frequency
000b – 6 frames     100b – 3 frames
001b – 32 frames    101b – 4 frames
010b – 64 frames    110b – 5 frame
011b – 128 frames   111b – 2 frame
D[2:0] : Define end page address
000b – PAGE0        011b – PAGE3        110b – PAGE6
001b – PAGE1        100b – PAGE4        111b – PAGE7
010b – PAGE2        101b – PAGE5
E[6:0] : Define start column address (RESET = 00h)
F[6:0] : Define end column address (RESET = 7Fh)
Notes:
(1) The value of D[2:0] must be larger than or equal to
B[2:0]
(2) The value of F[6:0] must be larger than or equal to
E[6:0]
Mask :  [ 0 0  1  0  0  1  1  X0 ]
        [ 0 0  0  0  0  0  0  0  ]
        [ 0 0  0  0  0  B2 B1 B0 ]
        [ 0 0  0  0  0  C2 C1 C0 ]
        [ 0 0  0  0  0  D2 D1 D0 ]
        [ 0 E6 E5 E4 E3 E2 E1 E0 ]
        [ 0 F6 F5 F4 F3 F2 F1 F0 ]
*/
static const uint8_t CMD_CONTINUOUS_HOR_SCROLL = 0x26;

/*
29h, X1X0=01b : Vertical and Right Horizontal Scroll
2Ah, X1X0=10b : Vertical and Left Horizontal Scroll
A[0] : Set number of column scroll offset
 0b No horizontal scroll
 1b Horizontal scroll by 1 column
B[2:0] : Define start page address
000b – PAGE0    011b – PAGE3    110b – PAGE6
001b – PAGE1    100b – PAGE4    111b – PAGE7
010b – PAGE2    101b – PAGE5
C[2:0] : Set time interval between each scroll step in
terms of frame frequency
000b – 6 frames     100b – 3 frames
001b – 32 frames    101b – 4 frames
010b – 64 frames    110b – 5 frame
011b – 128 frames   111b – 2 frame
D[2:0] : Define end page address
000b – PAGE0    011b – PAGE3    110b – PAGE6
001b – PAGE1    100b – PAGE4    111b – PAGE7
010b – PAGE2    101b – PAGE5
E[5:0] : Vertical scrolling offset
 e.g. E[5:0]= 01h refer to offset =1 row
 E[5:0] =3Fh refer to offset =63 rows
F[6:0] : Define the start column address (RESET =
00h)
G[6:0] : Define the end column address (RESET =
7Fh)
Note
(1) The value of D[2:0] must be larger than or equal
to B[2:0]
(2) The value of E[5:0] must be less than B[6:0] in
A3h
(3) The value of G[6:0] must be larger than or equal
to F[6:0]
Mask :  [ 0 0  1  0  1  0  X1 X0 ]
        [ 0 0  0  0  0  0  0  A0 ]
        [ 0 0  0  0  0  B2 B1 B0 ]
        [ 0 0  0  0  0  C2 C1 C0 ]
        [ 0 0  0  0  0  D2 D1 D0 ]
        [ 0 0  E5 E4 E3 E2 E1 E0 ]
        [ 0 F6 F5 F4 F3 F2 F1 F0 ]
        [ 0 G6 G5 G4 G3 G2 G1 G0 ]

*/
static const uint8_t CMD_CONTINUOUS_VERHOR_SCROLL = 0x29;

// Stop scrolling that is configured by command
// 26h/27h/29h/2Ah.
// Note
// (1)
//  After sending 2Eh command to deactivate the scrolling
// action, the ram data needs to be rewritten.
// Mask : [0 0 1 0 1 1 1 0]
static const uint8_t CMD_DEACTIVATE_SCROLL = 0x2E;

// Start scrolling that is configured by the scrolling setup
// commands :26h/27h/29h/2Ah with the following valid
// sequences:
// Valid command sequence 1: 26h ;2Fh.
// Valid command sequence 2: 27h ;2Fh.
// Valid command sequence 3: 29h ;2Fh.
// Valid command sequence 4: 2Ah ;2Fh.
// For example, if “26h; 2Ah; 2Fh.” commands are
// issued, the setting in the last scrolling setup command,
// i.e. 2Ah in this case, will be executed. In other words,
// setting in the last scrolling setup command overwrites
// the setting in the previous scrolling setup commands.
// Mask : [ 0 0 1 0 1 1 1 1 ]
static const uint8_t CMD_ACTIVATE_SCROLL = 0x2F;

// A[5:0] : Set No. of rows in top fixed area. The No. of
// rows in top fixed area is referenced to the top
// of the GDDRAM (i.e. row 0). [RESET = 0]
// B[6:0] : Set No. of rows in scroll area. This is the
// number of rows to be used for vertical
// scrolling. The scroll area starts in the first
// row below the top fixed area. [RESET = 64]
// Note
// (1) A[5:0]+B[6:0] <= MUX ratio
// (2) B[6:0] <= MUX ratio
// (3a) Vertical scrolling offset (E[5:0] in 29h/2Ah) <
// B[6:0]
// (3b) Set Display Start Line (X5X4X3X2X1X0 of
// 40h~7Fh) < B[6:0]
// (4) The last row of the scroll area shifts to the first row
// of the scroll area.
// (5) For 64d MUX display
//  A[5:0] = 0, B[6:0]=64 : whole area scrolls
//  A[5:0] = 0, B[6:0] < 64 : top area scrolls
//  A[5:0] + B[6:0] < 64 : central area scrolls
//  A[5:0] + B[6:0] = 64 : bottom area scrolls
// Mask :   [ 1 0  1  0  0  0  1  1 ]
//          [ 0 0  A5 A4 A3 A2 A1 A0 ]
//          [ 0 B6 B5 B4 B3 B2 B1 B0 ]
static const uint8_t CMD_VERTICAL_SCROLL_AREA = 0xA3;

// 2Ch, X[0]=0, Right Horizontal Scroll by one column
// 2Dh, X[0]=1, Left Horizontal Scroll by one column
// A[7:0] : Dummy byte (Set as 00h)
// B[2:0] : Define start page address
// 000b – PAGE0 011b – PAGE3 110b – PAGE6
// 001b – PAGE1 100b – PAGE4 111b – PAGE7
// 010b – PAGE2 101b – PAGE5
// C[7:0] : Dummy byte (Set as 01h)
// D[2:0] : Define end page address
// 000b – PAGE0 011b – PAGE3 110b – PAGE6
// 001b – PAGE1 100b – PAGE4 111b – PAGE7
// 010b – PAGE2 101b – PAGE5

// E[6:0] : Define start column address (RESET = 00h)
// F[6:0] : Define end column address (RESET = 7Fh)
// Note
// (1) The value of D[2:0] must be larger than or equal to
// B[2:0]
// (2) The value of F[6:0] must be larger than E[6:0]
// (3) A delay time of 2 frame frequency must be set if
// sending the command of 2Ch / 2Dh consecutively
// Mask :   [ 0 0  1  0  1  1  0  X0 ]
//          [ 0 0  0  0  0  0  0  0  ]
//          [ 0 0  0  0  0  B2 B1 B0 ]
//          [ 0 0  0  0  0  0  0  1 ]
//          [ 0 0  0  0  0  D2 D1 D0 ]
//          [ 0 E6 E5 E4 E3 E2 E1 E0 ]
//          [ 0 F6 F5 F4 F3 F2 F1 F0 ]
static const uint8_t CMD_CONTENT_SCROLL_SETUP = 0x2C;

// A[5:4] = 00b Disable Fade Out / Blinking Mode[RESET]
// A[5:4] = 10b Enable Fade Out mode.
// Once Fade Out mode is enabled, contrast decrease
// gradually to all pixels OFF. Output follows RAM content
// when Fade mode is disabled.
// A[5:4] = 11b Enable Blinking mode.
// Once Blinking mode is enabled, contrast decrease
// gradually to all pixels OFF and then contrast increase
// gradually to normal display. This process loop
// continuously until the Blinking mode is disabled.
// A[3:0] : Set time interval for each fade step
// A[3:0] Time interval for each fade step
// 0000b 8 Frames
// 0001b 16 Frames
// 0010b 24 Frames
// 1111b 128 Frames
// Note
// (1) Refer to section 1.4.1 for details
// Mask :   [ 0 0 1  0  0  0  1  1 ]
//          [ 0 0 A5 A4 A3 A2 A1 A0 ]
static const uint8_t CMD_FADE_OUT_BLINKING = 0x23;

// A[0] = 0b Disable Zoom in Mode [RESET]
// A[0] = 1b Enable Zoom in Mode
// Note
// (1) The panel must be in alternative COM pin
// configuration (command DAh A[4] =1)
// (2) Refer to section 1.4.2 for details
static const uint8_t ZOOM_IN = 0xD6;

} // namespace ssd1315::REGISTERS