#include "w25q32bv_common.h"
#include <utility>
#include <algorithm>

std::vector<uint8_t> form_cmd_buf(uint8_t cmd, uint32_t addr, uint8_t addr_size)
{
    std::vector<uint8_t> result;
    result.reserve(addr_size + 1);
    result.push_back(cmd);
    std::vector<uint8_t> addr_buf = form_byte_buf<uint32_t>(addr, addr_size);
    result.insert(result.end(), addr_buf.begin(), addr_buf.end());
    return result;
}