#include "i2c_device.h"

/**
 * @brief Конструктор класса
 * @param i2c <i2c_inst_t *> - сущность i2c в контексте pico sdk
 * @param device_address <uint8_t> - адрес устройства на шине I2C
 * @param buffer_size <size_t> - размер буффера (максимальный пакет I2C, который используется этим устройством)
 * @param timeout_us <size_t> - время ожидания (микросекунды) пакета при обращении по I2C(см. read_register,
 * write_register)
 */
I2CDevice::I2CDevice(i2c_inst_t *i2c, uint8_t device_address, size_t buffer_size, size_t timeout_us)
    : i2c_(i2c), device_address_(device_address), data_buffer_(buffer_size), timeout_us_(timeout_us)
{
}

/**
 * @brief Конструктор класса
 * @param i2c <i2c_inst_t *> - сущность i2c в контексте pico sdk
 * @param device_address <uint8_t> - адрес устройства на шине I2C
 * @param buffer_size <size_t> - размер буффера (максимальный пакет I2C, который используется этим устройством)
 */
I2CDevice::I2CDevice(i2c_inst_t *i2c, uint8_t device_address, size_t buffer_size)
    : I2CDevice(i2c, device_address, buffer_size, I2CDEVICE_DEFAULT_TIMEOUT_US)
{
}

/**
 * @brief Конструктор класса
 * @param i2c <i2c_inst_t *> - сущность i2c в контексте pico sdk
 * @param device_address <uint8_t> - адрес устройства на шине I2C
 */
I2CDevice::I2CDevice(i2c_inst_t *i2c, uint8_t device_address)
    : I2CDevice(i2c, device_address, I2CDEVICE_DEFAULT_MAX_BUFFER_SIZE)
{
}

/**
 * @brief Чтение регистра(ов) памяти.
 * @param reg <uint8_t> - регистр памяти
 * @param n_regs <size_t> - количество считываемых байт (из data_buffer_)
 */
void I2CDevice::read_register(uint8_t reg, size_t n_regs)
{
    data_buffer_[0] = reg;
    i2c_write_timeout_us(i2c_, device_address_, data_buffer_.data(), 1, true, timeout_us_);
    i2c_read_timeout_us(i2c_, device_address_, data_buffer_.data(), n_regs, false, timeout_us_);
}

/**
 * @brief Запись регистра(ов) памяти.
 * @param reg <uint8_t> - регистр памяти
 * @param n_regs <size_t> - количество записываемых байт (из data_buffer_)
 */
void I2CDevice::write_register(uint8_t reg, size_t n_regs)
{
    uint8_t buffer[++n_regs];
    buffer[0] = reg;
    for (uint reg_cnt = 0; reg_cnt < n_regs; ++reg_cnt)
    {
        buffer[reg_cnt + 1] = data_buffer_.at(reg_cnt);
    }
    i2c_write_timeout_us(i2c_, device_address_, buffer, n_regs, false, timeout_us_);
}
