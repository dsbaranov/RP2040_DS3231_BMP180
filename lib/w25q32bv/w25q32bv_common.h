#pragma once
#include <cstdint>
#include <vector>

/// @brief Преобразует переменную value типа T в массив байт с заданным размером байт size
/// @return vector<uint8_t>(size) байт от value или {} если size == 0 или size > sizeof(T)
template <typename T>
std::vector<uint8_t> form_byte_buf(T value, size_t size)
{
    if (size == 0 || size > sizeof(T))
        return {};
    uint8_t *value_ptr = (uint8_t *)value;
    std::vector<uint8_t> result(value_ptr, value_ptr + size);
    return {result.rbegin(), result.rend()};
}

/// @brief Формирует вектор из команды и трёх младших байтов адреса.
/// @param cmd команда
/// @param addr адрес регистра
/// @return
std::vector<uint8_t> form_cmd_buf(uint8_t cmd, uint32_t addr, uint8_t addr_size = 3u);