#include "i2c_eeprom_device.h"

void EEPROMDevice::read_register(uint16_t reg, size_t n_bytes)
{
    uint8_t device_address = I2CDevice::get_device_address();
    const size_t &timeout_us = I2CDevice::get_timeout_us();
    data_buffer_[0] = static_cast<uint8_t>((reg >> 8) & 0xFF);
    data_buffer_[1] = static_cast<uint8_t>(reg & 0xFF);
    i2c_write_timeout_us(i2c_, device_address, data_buffer_.data(), sizeof(reg), true, timeout_us);
    i2c_read_timeout_us(i2c_, device_address, data_buffer_.data(), n_bytes, false, timeout_us);
}

void EEPROMDevice::write_register(uint16_t reg, size_t n_bytes)
{
    unsigned reg_size = sizeof(reg);
    uint8_t device_address = I2CDevice::get_device_address();
    const size_t &timeout_us = I2CDevice::get_timeout_us();
    std::vector<uint8_t> buffer(n_bytes + reg_size, 0);
    buffer[0] = static_cast<uint8_t>((reg >> 8) & 0xFF);
    buffer[1] = static_cast<uint8_t>(reg & 0xFF);
    std::copy(data_buffer_.begin(), data_buffer_.begin() + n_bytes, buffer.begin() + reg_size);
    i2c_write_timeout_us(i2c_, device_address, buffer.data(), n_bytes + reg_size, false, timeout_us);
}
