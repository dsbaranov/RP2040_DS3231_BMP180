#include "ds3231/ds3231.h"
#include "ds3231/ds3231_common.h"

namespace DS3231
{

DS3231::DS3231(i2c_inst_t *i2c) : I2CDevice(i2c, REGISTERS::ADDR)
{
}

void DS3231::read_bulk_date_time_block()
{
    I2CDevice::read_register(REGISTERS::SECOND, 7);
    uint8_t reg_cnt = 0;
    datetime_.seconds = decode_seconds(I2CDevice::data_buffer_[reg_cnt++]);
    datetime_.minutes = decode_minutes(I2CDevice::data_buffer_[reg_cnt++]);
    datetime_.hours = decode_hours(I2CDevice::data_buffer_[reg_cnt++]);
    datetime_.dow = decode_dow(I2CDevice::data_buffer_[reg_cnt++]);
    datetime_.day = decode_day(I2CDevice::data_buffer_[reg_cnt++]);
    datetime_.month = decode_month(I2CDevice::data_buffer_[reg_cnt++]);
    datetime_.year = decode_year(I2CDevice::data_buffer_[reg_cnt]);
}

uint8_t DS3231::decode_seconds(uint8_t value)
{
    return common::ByteBinDecToDec(value);
}

uint8_t DS3231::decode_minutes(uint8_t value)
{
    return common::ByteBinDecToDec(value);
}

uint8_t DS3231::decode_hours(uint8_t value)
{
    datetime_.is_meridial = (value >> 6) & 0x01;
    datetime_.is_pm = (value >> 5) & 0x01;
    if (datetime_.is_meridial)
    {
        return common::ByteBinDecToDec(value & 0x1F);
    }
    else
    {
        return common::ByteBinDecToDec(value & 0x3F);
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
    return common::ByteBinDecToDec(value);
}

uint8_t DS3231::decode_month(uint8_t value)
{
    bool new_age = static_cast<bool>((value >> 7) & 0x01);
    if (new_age)
    {
        datetime_.age++;
    }
    return value & 0x1F;
}

uint8_t DS3231::decode_year(uint8_t value)
{
    return common::ByteBinDecToDec(value);
}

void DS3231::read_seconds_register()
{
    I2CDevice::read_register(REGISTERS::SECOND, 1);
    datetime_.seconds = decode_seconds(I2CDevice::data_buffer_[0]);
}

void DS3231::read_minutes_register()
{
    I2CDevice::read_register(REGISTERS::MINUTE, 1);
    datetime_.minutes = decode_minutes(I2CDevice::data_buffer_[0]);
}

void DS3231::read_hours_register()
{
    I2CDevice::read_register(REGISTERS::HOUR, 1);
    datetime_.hours = decode_hours(I2CDevice::data_buffer_[0]);
}

void DS3231::read_dow_register()
{
    I2CDevice::read_register(REGISTERS::DOW, 1);
    datetime_.dow = decode_dow(I2CDevice::data_buffer_[0]);
}

void DS3231::read_day_register()
{
    I2CDevice::read_register(REGISTERS::DAY, 1);
    datetime_.day = decode_day(I2CDevice::data_buffer_[0]);
}

void DS3231::read_month_register()
{
    I2CDevice::read_register(REGISTERS::MONTH, 1);
    datetime_.month = decode_month(I2CDevice::data_buffer_[0]);
}

void DS3231::read_year_register()
{
    I2CDevice::read_register(REGISTERS::YEAR, 1);
    datetime_.year = decode_year(I2CDevice::data_buffer_[0]);
}

DS3231 &DS3231::set_seconds_register(uint8_t value)
{
    datetime_.seconds = value;
    I2CDevice::data_buffer_[0] = common::ByteDecToBinDec(datetime_.seconds);
    I2CDevice::write_register(REGISTERS::SECOND, 1u);
    return *this;
}

DS3231 &DS3231::set_minutes_register(uint8_t value)
{
    datetime_.minutes = value;
    I2CDevice::data_buffer_[0] = common::ByteDecToBinDec(datetime_.minutes);
    I2CDevice::write_register(REGISTERS::MINUTE, 1u);
    return *this;
}

DS3231 &DS3231::set_hours_register(uint8_t value, uint8_t is_meridial, uint8_t is_am)
{
    datetime_.hours = is_meridial ? value % 13 : value;
    datetime_.is_meridial = is_meridial;
    datetime_.is_pm = is_am;
    I2CDevice::data_buffer_[0] = common::ByteDecToBinDec(datetime_.hours);
    if (datetime_.is_meridial)
    {
        data_buffer_[0] |= 0b01100000 & ((datetime_.is_meridial << 6u) | (datetime_.is_pm << 5u));
    }
    write_register(REGISTERS::HOUR, 1);
    return *this;
}

uint8_t DS3231::GetSeconds()
{
    read_seconds_register();
    return datetime_.seconds;
}

uint8_t DS3231::GetMinutes()
{
    read_minutes_register();
    return datetime_.minutes;
}

uint8_t DS3231::GetHours()
{
    read_hours_register();
    return datetime_.hours;
}
uint8_t DS3231::GetDow()
{
    read_dow_register();
    return datetime_.dow;
}
uint8_t DS3231::GetDay()
{
    read_day_register();
    return datetime_.day;
}
uint8_t DS3231::GetMonth()
{
    read_month_register();
    return datetime_.month;
}
uint8_t DS3231::GetAge()
{
    return datetime_.age;
}
uint8_t DS3231::GetYear()
{
    read_year_register();
    return datetime_.year;
}
std::string DS3231::GetFormattedSeconds()
{
    return common::FormatDecWithLeadingZero(GetSeconds());
}
std::string DS3231::GetFormattedMinutes()
{
    return common::FormatDecWithLeadingZero(GetMinutes());
}
std::string DS3231::GetFormattedHours()
{
    return common::FormatDecWithLeadingZero(GetHours());
}
std::string DS3231::GetFormattedDay()
{
    return common::FormatDecWithLeadingZero(GetDay());
}
std::string DS3231::GetFormattedMonth()
{
    return common::FormatDecWithLeadingZero(GetMonth());
}
std::string DS3231::GetFormattedYear()
{
    return common::FormatDecWithLeadingZero(GetYear());
}

domain::DateTime DS3231::GetDateTime()
{
    read_bulk_date_time_block();
    return datetime_;
}

const domain::DateTime &DS3231::GetDateTimeConst()
{
    return datetime_;
}

}; // namespace DS3231
