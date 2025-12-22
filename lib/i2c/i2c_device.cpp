#include "i2c_device.h"

I2CDevice::I2CDevice(i2c_inst_t *i2c, uint8_t device_address) : i2c_(i2c), device_address_(device_address)
{
}

void I2CDevice::read_register(uint8_t reg, uint8_t n_regs)
{
    data_buffer_[0] = reg;
    i2c_write_timeout_us(i2c_, device_address_, data_buffer_, 1, true, I2CDEVICE_TIMEOUT_US);
    i2c_read_timeout_us(i2c_, device_address_, data_buffer_, n_regs, false, I2CDEVICE_TIMEOUT_US);
}

void I2CDevice::write_register(uint8_t reg, uint8_t n_regs)
{
    uint8_t buffer[++n_regs];
    buffer[0] = reg;
    for (uint reg_cnt = 0; reg_cnt < n_regs; ++reg_cnt)
    {
        buffer[reg_cnt + 1] = data_buffer_[reg_cnt];
    }
    i2c_write_timeout_us(i2c_, device_address_, buffer, n_regs, false, I2CDEVICE_TIMEOUT_US);
}
