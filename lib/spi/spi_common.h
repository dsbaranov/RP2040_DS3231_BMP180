#pragma once

#include <cstdint>
#include <vector>

uint8_t get_left_shifted_byte(uint32_t value, uint8_t shift);
std::vector<uint8_t> form_cmd_buf(uint8_t cmd, uint32_t addr);