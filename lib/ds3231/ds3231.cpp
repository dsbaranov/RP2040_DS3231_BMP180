#include "ds3231.h"
#include "ds3231_common.h"

namespace DS3231
{

DS3231::DS3231(i2c_inst_t *i2c) : I2CDevice(i2c, REGISTERS::ADDR, 11u)
{
}

void DS3231::read_bulk_date_time_block()
{
    I2CDevice::read_register(REGISTERS::SECOND, 7);
    uint8_t reg_cnt = 0;
    datetime_.seconds = decode_seconds(I2CDevice::data_buffer_[reg_cnt++]);
    datetime_.minutes = decode_minutes(I2CDevice::data_buffer_[reg_cnt++]);
    domain::IHourData iHour = decode_hours(I2CDevice::data_buffer_[reg_cnt++]);
    datetime_.hours = iHour.hours;
    datetime_.is_meridial = iHour.is_meridial;
    datetime_.is_pm = iHour.is_pm;
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
domain::IHourData DS3231::decode_hours(uint8_t hours)
{
    domain::IHourData iHourData;
    iHourData.is_meridial = (hours >> 6) & 0x01;
    iHourData.is_pm = (hours >> 5) & 0x01;
    if (iHourData.is_meridial == 1)
    {
        iHourData.hours = common::ByteBinDecToDec(hours & 0x1F);
    }
    else
    {
        iHourData.hours = common::ByteBinDecToDec(hours & 0x3F);
    }
    return iHourData;
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
    return common::ByteDecToBinDec(hours) | (0x60 & ((is_meridial << 6u) | (is_pm << 5u)));
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
    default:
        result = 1;
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

void DS3231::set_alarm(const domain::IAlarm1 &ialarm1)
{
    alarm1_ = ialarm1;
    data_buffer_[0] = encode_seconds(ialarm1.seconds) | (ialarm1.seconds_off << 7u);
    data_buffer_[1] = encode_minutes(ialarm1.minutes) | (ialarm1.minutes_off << 7u);
    data_buffer_[2] = encode_hours(ialarm1.hours, ialarm1.is_meridial, ialarm1.is_pm) | (ialarm1.hours_off << 7u);
    data_buffer_[3] = (0x00 | (ialarm1.day_off << 7u)) | (ialarm1.day_is_dow << 6u);
    data_buffer_[3] |= ialarm1.day_is_dow == 1 ? encode_dow(ialarm1.day) : encode_day(ialarm1.day);
    write_register(ALARM1_SEC, 4u);
}
void DS3231::set_alarm(domain::IAlarm1 &&ialarm1)
{
    alarm1_ = ialarm1;
    data_buffer_[0] = encode_seconds(std::move(ialarm1.seconds)) | (std::move(ialarm1.seconds_off) << 7u);
    data_buffer_[1] = encode_minutes(std::move(ialarm1.minutes)) | (std::move(ialarm1.minutes_off) << 7u);
    data_buffer_[2] = encode_hours(std::move(ialarm1.hours), std::move(ialarm1.is_meridial), std::move(ialarm1.is_pm)) |
                      (std::move(ialarm1.hours_off) << 7u);
    data_buffer_[3] = (0x00 | (std::move(ialarm1.day_off) << 7u)) | (ialarm1.day_is_dow << 6u);
    data_buffer_[3] |=
        ialarm1.day_is_dow == 1 ? encode_dow(std::move(ialarm1.day)) : encode_day(std::move(ialarm1.day));
    write_register(ALARM1_SEC, 4u);
}

void DS3231::set_alarm(const domain::IAlarm2 &ialarm2)
{
    alarm2_ = ialarm2;
    data_buffer_[0] = encode_minutes(ialarm2.minutes) | (ialarm2.minutes_off << 7u);
    data_buffer_[1] = encode_hours(ialarm2.hours, ialarm2.is_meridial, ialarm2.is_pm) | (ialarm2.hours_off << 7u);
    data_buffer_[2] = (0x00 | (ialarm2.day_off << 7u)) | (ialarm2.day_is_dow << 6u);
    data_buffer_[2] |= ialarm2.day_is_dow == 1 ? encode_dow(ialarm2.day) : encode_day(ialarm2.day);
    write_register(ALARM2_MIN, 3);
}

void DS3231::set_alarm(domain::IAlarm2 &&ialarm2)
{
    alarm2_ = ialarm2;
    data_buffer_[0] = encode_minutes(std::move(ialarm2.minutes)) | (std::move(ialarm2.minutes_off) << 7u);
    data_buffer_[1] = encode_hours(std::move(ialarm2.hours), std::move(ialarm2.is_meridial), std::move(ialarm2.is_pm)) |
                      (ialarm2.hours_off << 7u);
    data_buffer_[2] = (0x00 | (std::move(ialarm2.day_off) << 7u)) | (ialarm2.day_is_dow << 6u);
    data_buffer_[2] |= ialarm2.day_is_dow == 1 ? encode_dow(std::move(ialarm2.day)) : encode_day(ialarm2.day);
    write_register(ALARM2_MIN, 3);
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
    domain::IHourData iHour = decode_hours(I2CDevice::data_buffer_[0]);
    datetime_.is_meridial = iHour.is_meridial;
    datetime_.is_pm = iHour.is_pm;
    datetime_.hours = iHour.hours;
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
    Controls.EOSC = (data_buffer_[0] >> cnt--) & 0x01;
    Controls.BBSQW = (data_buffer_[0] >> cnt--) & 0x01;
    Controls.CONV = (data_buffer_[0] >> cnt--) & 0x01;
    Controls.RS2 = (data_buffer_[0] >> cnt--) & 0x01;
    Controls.RS1 = (data_buffer_[0] >> cnt--) & 0x01;
    Controls.INTCN = (data_buffer_[0] >> cnt--) & 0x01;
    Controls.A2IE = (data_buffer_[0] >> cnt--) & 0x01;
    Controls.A1IE = data_buffer_[0] & 0x01;
}

void DS3231::read_state()
{
    uint8_t cnt = 1;
    I2CDevice::read_register(REGISTERS::CTL_STA, cnt);
    State.A1F = (data_buffer_[0] & cnt);
    State.A2F = (data_buffer_[0] >> cnt++) & 0x01;
    State.BSY = (data_buffer_[0] >> cnt++) & 0x01;
    State.EN32 = (data_buffer_[0] >> cnt) & 0x01;
    cnt = 7u;
    State.OSF = (data_buffer_[0] >> cnt) & 0x01;
}

void DS3231::set_state()
{
    data_buffer_[0] = 0x00 | ((State.OSF & 0x01) << 7u) | ((State.EN32 & 0x01) << 3u) | ((State.BSY & 0x01) << 2u) |
                      ((State.A2F & 0x01) << 1u) | (State.A1F & 0x01);
    write_register(REGISTERS::CTL_STA, 1);
}

DS3231 &DS3231::setSeconds(uint8_t value)
{
    datetime_.seconds = value % 60;
    I2CDevice::data_buffer_[0] = encode_seconds(datetime_.seconds);
    I2CDevice::write_register(REGISTERS::SECOND, 1u);
    return *this;
}
DS3231 &DS3231::setMinutes(uint8_t value)
{
    datetime_.minutes = value % 60;
    I2CDevice::data_buffer_[0] = encode_minutes(datetime_.minutes);
    I2CDevice::write_register(REGISTERS::MINUTE, 1u);
    return *this;
}
DS3231 &DS3231::setHours(uint8_t value, uint8_t is_meridial, uint8_t is_am)
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
DS3231 &DS3231::setDow(uint8_t value)
{
    datetime_.dow = value % 7;
    I2CDevice::data_buffer_[0] = encode_dow(datetime_.dow);
    write_register(REGISTERS::DOW, 1);
    return *this;
}
DS3231 &DS3231::setDay(uint8_t value)
{
    datetime_.day = std::min(uint8_t(31), value);
    I2CDevice::data_buffer_[0] = encode_day(datetime_.day);
    write_register(REGISTERS::DAY, 1);
    return *this;
}
DS3231 &DS3231::setMonth(uint8_t value)
{
    datetime_.month = std::max(std::min(uint8_t(12u), value), uint8_t(1));
    I2CDevice::data_buffer_[0] = datetime_.month;
    write_register(REGISTERS::MONTH, 1);
    return *this;
}
DS3231 &DS3231::setYear(uint16_t value)
{
    datetime_.age = value / 100;
    datetime_.year = value % 100;
    I2CDevice::data_buffer_[0] = encode_year(datetime_.year);
    write_register(REGISTERS::YEAR, 1);
    return *this;
}

void DS3231::readAlarm2()
{
    read_register(REGISTERS::ALARM2_MIN, 3);
    alarm2_.minutes = decode_minutes(data_buffer_[0] & 0x7F);
    alarm2_.minutes_off = (data_buffer_[0] >> 7u) & 0x01;
    domain::IHourData iHour = decode_hours(data_buffer_[1] & 0x7F);
    alarm2_.hours = iHour.hours;
    alarm2_.is_pm = iHour.is_pm;
    alarm2_.is_meridial = iHour.is_meridial;
    alarm2_.hours_off = (data_buffer_[1] >> 7u) & 0x01;
    alarm2_.day_off = (data_buffer_[2] >> 7u) & 0x01;
    alarm2_.day_is_dow = (data_buffer_[2] >> 6u) & 0x01;
    alarm2_.day = decode_day(data_buffer_[2] & 0x3F);
    alarm2_.dow = decode_dow(data_buffer_[2] & 0x7);
}

domain::IAlarm2 &DS3231::Alarm2()
{
    return alarm2_;
}

void DS3231::readAlarm1()
{
    read_register(REGISTERS::ALARM1_SEC, 4);
    alarm1_.seconds_off = (data_buffer_[0] >> 7u) & 0x01;
    alarm1_.seconds = decode_seconds(data_buffer_[0] & 0x7F);
    alarm1_.minutes = decode_minutes(data_buffer_[1] & 0x7F);
    alarm1_.minutes_off = (data_buffer_[1] >> 7u) & 0x01;
    domain::IHourData iHour = decode_hours(data_buffer_[2] & 0x7F);
    alarm1_.hours = iHour.hours;
    alarm1_.is_pm = iHour.is_pm;
    alarm1_.is_meridial = iHour.is_meridial;
    alarm1_.hours_off = (data_buffer_[2] >> 7u) & 0x01;
    alarm1_.day_off = (data_buffer_[3] >> 7u) & 0x01;
    alarm1_.day_is_dow = (data_buffer_[3] >> 6u) & 0x01;
    alarm1_.day = decode_day(data_buffer_[3] & 0x3F);
    alarm1_.dow = decode_dow(data_buffer_[3] & 0x7);
}

domain::IAlarm1 &DS3231::Alarm1()
{
    return alarm1_;
}

void DS3231::setDateTimeBlock(const domain::IDateTimeDetailed &datetime)
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

void DS3231::init()
{
    readControls();
    Controls.EOSC = 0;
    setControls();
}

uint8_t DS3231::getSeconds()
{
    read_seconds_register();
    return datetime_.seconds;
}

uint8_t DS3231::getMinutes()
{
    read_minutes_register();
    return datetime_.minutes;
}

uint8_t DS3231::getHours()
{
    read_hours_register();
    return datetime_.hours;
}
uint8_t DS3231::getDow()
{
    read_dow_register();
    return datetime_.dow;
}
uint8_t DS3231::getDay()
{
    read_day_register();
    return datetime_.day;
}
uint8_t DS3231::getMonth()
{
    read_month_register();
    return datetime_.month;
}
uint8_t DS3231::getAge()
{
    return datetime_.age;
}
uint8_t DS3231::getYear()
{
    read_year_register();
    return datetime_.year;
}
std::string DS3231::getFormattedSeconds()
{
    return common::FormatDecWithLeadingZero(getSeconds());
}
std::string DS3231::getFormattedMinutes()
{
    return common::FormatDecWithLeadingZero(getMinutes());
}
std::string DS3231::getFormattedHours()
{
    return common::FormatDecWithLeadingZero(getHours());
}
std::string DS3231::getFormattedDay()
{
    return common::FormatDecWithLeadingZero(getDay());
}
std::string DS3231::getFormattedMonth()
{
    return common::FormatDecWithLeadingZero(getMonth());
}
std::string DS3231::getFormattedYear()
{
    return common::FormatDecWithLeadingZero(getYear());
}

domain::IDateTimeDetailed DS3231::getDateTime()
{
    read_bulk_date_time_block();
    return datetime_;
}

const domain::IDateTimeDetailed &DS3231::getDateTimeConst() const
{
    return datetime_;
}

void DS3231::readControls()
{
    read_controls();
}

DS3231 &DS3231::setControls()
{
    data_buffer_[0] = 0x00 | ((Controls.EOSC & 0x01) << 7u) | ((Controls.BBSQW & 0x01) << 6u) |
                      ((Controls.CONV & 0x01) << 5u) | ((Controls.RS1 & 0x01) << 4u) | ((Controls.RS2 & 0x01) << 3u) |
                      ((Controls.INTCN & 0x01) << 2u) | ((Controls.A1IE & 0x01) << 1u) | (Controls.A2IE & 0x01);
    write_register(REGISTERS::CONTROL, 1);
    return *this;
}
void DS3231::readState()
{
    read_state();
}

DS3231 &DS3231::setState()
{
    set_state();
    return *this;
}
} // namespace DS3231
