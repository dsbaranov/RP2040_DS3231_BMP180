#pragma once
#include "i2c/i2c_eeprom_device.h"
#include "ft24c256a_registers.h"

class FT24C256A : EEPROMDevice
{
private:
    static const uint32_t PAGE_SIZE = 64;
    static const uint32_t NUMBER_OF_PAGES = 512;

public:
    FT24C256A(i2c_inst_t *i2c) : EEPROMDevice(i2c, DEVICE_ADDRESS, PAGE_SIZE) {}
    uint32_t get_number_of_pages() const override;
    uint32_t get_page_size() const override;

    void read_data();
    void write_data();
};