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

uint8_t DS3231::decode_seconds(uint8_t seconds)
{
    return common::ByteBinDecToDec(seconds);
}
uint8_t DS3231::decode_minutes(uint8_t minutes)
{
    return common::ByteBinDecToDec(minutes);
}
uint8_t DS3231::decode_hours(uint8_t hours)
{
    datetime_.is_meridial = (hours >> 6) & 0x01;
    datetime_.is_pm = (hours >> 5) & 0x01;
    if (datetime_.is_meridial)
    {
        return common::ByteBinDecToDec(hours & 0x1F);
    }
    else
    {
        return common::ByteBinDecToDec(hours & 0x3F);
    }
}
uint8_t DS3231::decode_dow(uint8_t dow)
{
    uint8_t result;
    switch (dow)
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
    return result;
}
uint8_t DS3231::decode_day(uint8_t day)
{
    return common::ByteBinDecToDec(day);
}
uint8_t DS3231::decode_month(uint8_t month)
{
    bool new_age = static_cast<bool>((month >> 7) & 0x01);
    if (new_age)
    {
        datetime_.age++;
    }
    return month & 0x1F;
}
uint8_t DS3231::decode_year(uint8_t year)
{
    return common::ByteBinDecToDec(year);
}

uint8_t DS3231::encode_seconds(uint8_t seconds)
{
    return common::ByteDecToBinDec(seconds);
}
uint8_t DS3231::encode_minutes(uint8_t minutes)
{
    return common::ByteDecToBinDec(minutes);
}
uint8_t DS3231::encode_hours(uint8_t hours, uint8_t is_meridial, uint8_t is_pm)
{
    return common::ByteDecToBinDec(hours) | (0b01100000 & ((is_meridial << 6u) | (is_pm << 5u)));
}
uint8_t DS3231::encode_dow(uint8_t dow)
{
    uint8_t result;
    switch (dow)
    {
    case 0:
        result = 2;
        break;
    case 1:
        result = 3;
        break;
    case 2:
        result = 4;
        break;
    case 3:
        result = 5;
        break;
    case 4:
        result = 6;
        break;
    case 5:
        result = 7;
        break;
    case 6:
        result = 1;
        break;
    }
    return result;
}
uint8_t DS3231::encode_day(uint8_t day)
{
    return common::ByteDecToBinDec(day);
}
uint8_t DS3231::encode_month(uint8_t month)
{
    return month;
}
uint8_t DS3231::encode_year(uint8_t year)
{
    return common::ByteDecToBinDec(year);
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

void DS3231::read_controls()
{
    I2CDevice::read_register(REGISTERS::CONTROL, 1);
    uint8_t cnt = 7;
    controls.EOSC = (data_buffer_[0] >> cnt--) & 0x01;
    controls.BBSQW = (data_buffer_[0] >> cnt--) & 0x01;
    controls.CONV = (data_buffer_[0] >> cnt--) & 0x01;
    controls.RS2 = (data_buffer_[0] >> cnt--) & 0x01;
    controls.RS1 = (data_buffer_[0] >> cnt--) & 0x01;
    controls.INTCN = (data_buffer_[0] >> cnt--) & 0x01;
    controls.A2IE = (data_buffer_[0] >> cnt--) & 0x01;
    controls.A1IE = data_buffer_[0] & 0x01;
}

DS3231 &DS3231::SetSeconds(uint8_t value)
{
    datetime_.seconds = value % 60;
    I2CDevice::data_buffer_[0] = encode_seconds(datetime_.seconds);
    I2CDevice::write_register(REGISTERS::SECOND, 1u);
    return *this;
}
DS3231 &DS3231::SetMinutes(uint8_t value)
{
    datetime_.minutes = value % 60;
    I2CDevice::data_buffer_[0] = encode_minutes(datetime_.minutes);
    I2CDevice::write_register(REGISTERS::MINUTE, 1u);
    return *this;
}
DS3231 &DS3231::SetHours(uint8_t value, uint8_t is_meridial, uint8_t is_am)
{
    if (is_meridial)
    {
        uint8_t meridial_value = value % 12;
        if (meridial_value == 0)
        {
            meridial_value = 12;
        }
        datetime_.hours = meridial_value;
    }
    else
    {
        datetime_.hours = value % 24;
    }
    datetime_.is_meridial = is_meridial;
    datetime_.is_pm = is_am;
    I2CDevice::data_buffer_[0] = encode_hours(datetime_.hours, datetime_.is_meridial, datetime_.is_pm);
    write_register(REGISTERS::HOUR, 1);
    return *this;
}
DS3231 &DS3231::SetDow(uint8_t value)
{
    datetime_.dow = value % 7;
    I2CDevice::data_buffer_[0] = encode_dow(datetime_.dow);
    write_register(REGISTERS::DOW, 1);
    return *this;
}
DS3231 &DS3231::SetDay(uint8_t value)
{
    datetime_.day = std::min(uint8_t(31), value);
    I2CDevice::data_buffer_[0] = encode_day(datetime_.day);
    write_register(REGISTERS::DAY, 1);
    return *this;
}
DS3231 &DS3231::SetMonth(uint8_t value)
{
    datetime_.month = std::max(std::min(uint8_t(12u), value), uint8_t(1));
    I2CDevice::data_buffer_[0] = datetime_.month;
    write_register(REGISTERS::MONTH, 1);
    return *this;
}
DS3231 &DS3231::SetYear(uint16_t value)
{
    datetime_.age = value / 100;
    datetime_.year = value % 100;
    I2CDevice::data_buffer_[0] = encode_year(datetime_.year);
    write_register(REGISTERS::YEAR, 1);
    return *this;
}

DS3231 &DS3231::SetAlarm1(uint8_t seconds, uint8_t minutes, uint8_t hours, bool is_meridial, bool is_pm, uint8_t day,
                          bool dow)
{
    data_buffer_[0] = common::ByteDecToBinDec(seconds);
    data_buffer_[1] = common::ByteDecToBinDec(minutes);
    data_buffer_[2] = common::ByteDecToBinDec(hours) | (0b01100000 & ((is_meridial << 6u) | (is_pm << 5u)));

    return *this;
}

DS3231 &DS3231::SetAlarm2(uint8_t minutes, uint8_t hours, bool is_meridian, bool is_pm, uint8_t day, bool dow)
{
    // TODO: insert return statement here
    return *this;
}

void DS3231::SetDateTimeBlock(const domain::DateTime &datetime)
{
    datetime_.seconds = datetime.seconds % 60;
    datetime_.minutes = datetime.minutes % 60;
    if (datetime.is_meridial)
    {
        uint8_t meridial_value = datetime.hours % 12;
        if (meridial_value == 0)
        {
            meridial_value = 12;
        }
        datetime_.hours = meridial_value;
    }
    else
    {
        datetime_.hours = datetime.hours % 24;
    }
    datetime_.is_meridial = datetime.is_meridial;
    datetime_.is_pm = datetime.is_pm;
    datetime_.dow = datetime.dow % 7;
    datetime_.day = std::min(uint8_t(31), datetime.day);
    datetime_.month = std::max(std::min(uint8_t(12u), datetime.month), uint8_t(1));
    datetime_.age = datetime.age % 100;
    datetime_.year = datetime.year % 100;

    uint8_t reg_cnt = 0;
    I2CDevice::data_buffer_[reg_cnt++] = encode_seconds(datetime_.seconds);
    I2CDevice::data_buffer_[reg_cnt++] = encode_minutes(datetime_.minutes);
    I2CDevice::data_buffer_[reg_cnt++] = encode_hours(datetime_.hours, datetime_.is_meridial, datetime_.is_pm);
    I2CDevice::data_buffer_[reg_cnt++] = encode_dow(datetime_.dow);
    I2CDevice::data_buffer_[reg_cnt++] = encode_day(datetime_.day);
    I2CDevice::data_buffer_[reg_cnt++] = encode_month(datetime_.month);
    I2CDevice::data_buffer_[reg_cnt++] = encode_year(datetime_.year);
    I2CDevice::write_register(REGISTERS::SECOND, reg_cnt);
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

void DS3231::ReadControls()
{
    read_controls();
}

DS3231 &DS3231::SetControls()
{
    data_buffer_[0] = 0x00 | ((controls.EOSC & 0x01) << 7u) | ((controls.BBSQW & 0x01) << 6u) |
                      ((controls.CONV & 0x01) << 5u) | ((controls.RS1 & 0x01) << 4u) | ((controls.RS2 & 0x01) << 3u) |
                      ((controls.INTCN & 0x01) << 2u) | ((controls.A1IE & 0x01) << 1u) | (controls.A2IE & 0x01);
    write_register(REGISTERS::CONTROL, 1);
    return *this;
}
}; // namespace DS3231
