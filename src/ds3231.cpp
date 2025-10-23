#include "ds3231.h"
#include "common.h"

namespace DS3231
{

DS3231::DS3231(i2c_inst_t *i2c) : i2c_(i2c)
{
}

void DS3231::read_register(uint8_t reg, uint8_t n_regs)
{
    data_buffer_[0] = reg;
    i2c_write_blocking(i2c_, REGISTERS::ADDR, data_buffer_, 1, true);
    i2c_read_blocking(i2c_, REGISTERS::ADDR, data_buffer_, n_regs, false);
}

void DS3231::write_register(uint8_t reg, uint8_t n_regs)
{
    uint8_t buffer[++n_regs];
    for (uint reg_cnt = 0; reg_cnt < n_regs; ++reg_cnt)
    {
        buffer[reg_cnt] = data_buffer_[reg_cnt];
    }
    i2c_write_blocking(i2c_, REGISTERS::ADDR, buffer, n_regs, false);
}

void DS3231::clear_register()
{
    for (uint8_t i = 0; i < 8; i++)
    {
        data_buffer_[i] = 0;
    }
}

uint8_t DS3231::decode_seconds(uint8_t value)
{
    return byte_bindec_to_dec(value);
}

uint8_t DS3231::decode_minutes(uint8_t value)
{
    return byte_bindec_to_dec(value);
}

uint8_t DS3231::decode_hours(uint8_t value)
{
    is_meridial_ = static_cast<bool>((value >> 6) & 0x01);
    is_pm_ = static_cast<bool>((value >> 5) & 0x01);
    if (is_meridial_)
    {
        return byte_bindec_to_dec(value & 0x1F);
    }
    else
    {
        return byte_bindec_to_dec(value & 0x3F);
    }
}

uint8_t DS3231::decode_dow(uint8_t value)
{
    uint result;
    switch (value)
    {
    case 1: // вс
        result = 6;
        break;
    case 2: // пн
        result = 0;
        break;
    case 3: // вт...
        result = 1;
        break;
    case 4:
        result = 2;
        break;
    case 5:
        result = 3;
        break;
    case 6:
        result = 4;
        break;
    case 7: //...сб
        result = 5;
        break;
    default:
        result = 0;
        break;
    }
    return 0;
}

uint8_t DS3231::decode_day(uint8_t value)
{
    return byte_bindec_to_dec(value);
}

uint8_t DS3231::decode_month(uint8_t value)
{
    bool new_age = static_cast<bool>((data_buffer_[0] >> 7) & 0x01);
    if (new_age)
    {
        age_++;
    }
    return data_buffer_[0] & 0x1F;
}

uint8_t DS3231::decode_year(uint8_t value)
{
    return byte_bindec_to_dec(value);
}

void DS3231::read_seconds_register()
{
    read_register(REGISTERS::SECOND, 1);
    seconds_ = decode_seconds(data_buffer_[0]);
}

void DS3231::read_minutes_register()
{
    read_register(REGISTERS::MINUTE, 1);
    minutes_ = decode_minutes(data_buffer_[0]);
}

void DS3231::read_hours_register()
{
    read_register(REGISTERS::HOUR, 1);
    hours_ = decode_hours(data_buffer_[0]);
}

void DS3231::read_dow_register()
{
    read_register(REGISTERS::DOW, 1);
    dow_ = decode_dow(data_buffer_[0]);
}

void DS3231::read_day_register()
{
    read_register(REGISTERS::DAY, 1);
    day_ = decode_day(data_buffer_[0]);
}

void DS3231::read_month_register()
{
    read_register(REGISTERS::MONTH, 1);

    month_ = decode_month(data_buffer_[0]);
}

void DS3231::read_year_register()
{
    read_register(REGISTERS::YEAR, 1);
    year_ = decode_year(data_buffer_[0]);
}

const uint8_t *DS3231::buffer()
{
    return data_buffer_;
}

uint8_t DS3231::get_seconds()
{
    read_seconds_register();
    return seconds_;
}

uint8_t DS3231::get_minutes()
{
    read_minutes_register();
    return minutes_;
}

uint8_t DS3231::get_hours()
{
    read_hours_register();
    return hours_;
}
uint8_t DS3231::get_dow()
{
    read_dow_register();
    return dow_;
}
uint8_t DS3231::get_day()
{
    read_day_register();
    return day_;
}
uint8_t DS3231::get_month()
{
    read_month_register();
    return month_;
}
uint8_t DS3231::get_age()
{
    return age_;
}
uint8_t DS3231::get_year()
{
    read_year_register();
    return year_;
}
}; // namespace DS3231
