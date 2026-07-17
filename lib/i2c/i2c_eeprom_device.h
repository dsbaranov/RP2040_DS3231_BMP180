#pragma once
#include "i2c_device.h"

class EEPROMDevice : I2CDevice
{
    EEPROMDevice() = delete;
    EEPROMDevice(const EEPROMDevice &) = delete;
    EEPROMDevice(EEPROMDevice &&) = delete;

protected:
    explicit EEPROMDevice(i2c_inst_t *i2c, uint8_t device_address, size_t buffer_size) : I2CDevice(i2c, device_address, buffer_size)
    {
    }

    std::vector<uint8_t> &data_buffer_ = I2CDevice::data_buffer_;

    void read_register(uint16_t reg, size_t n_bytes);
    void write_register(uint16_t reg, size_t n_bytes);

    virtual uint32_t get_number_of_pages() const = 0;
    virtual uint32_t get_page_size() const = 0;

    virtual ~EEPROMDevice() {};
};