#include "bmp180.h"
#include "bmp180_common.h"
#include <cmath>
namespace BMP180
{

BMP180::BMP180(i2c_inst_t *i2c) : I2CDevice(i2c, REGISTERS::ADDR, 22u)
{
}

bool BMP180::Ping()
{
    I2CDevice::read_register(REGISTERS::CHIP_ID, 1u);
    return data_buffer_[0] == 0x55;
}

void BMP180::GetCoefficients()
{
    read_register(REGISTERS::AC1, 22);
    uint8_t counter = 0;
    coefficients.AC1 = common::UnifyBytes<int16_t>(data_buffer_[counter++], data_buffer_[counter++]);
    coefficients.AC2 = common::UnifyBytes<int16_t>(data_buffer_[counter++], data_buffer_[counter++]);
    coefficients.AC3 = common::UnifyBytes<int16_t>(data_buffer_[counter++], data_buffer_[counter++]);
    coefficients.AC4 = common::UnifyBytes<uint16_t>(data_buffer_[counter++], data_buffer_[counter++]);
    coefficients.AC5 = common::UnifyBytes<uint16_t>(data_buffer_[counter++], data_buffer_[counter++]);
    coefficients.AC6 = common::UnifyBytes<uint16_t>(data_buffer_[counter++], data_buffer_[counter++]);
    coefficients.B1 = common::UnifyBytes<int16_t>(data_buffer_[counter++], data_buffer_[counter++]);
    coefficients.B2 = common::UnifyBytes<int16_t>(data_buffer_[counter++], data_buffer_[counter++]);
    coefficients.MB = common::UnifyBytes<int16_t>(data_buffer_[counter++], data_buffer_[counter++]);
    coefficients.MC = common::UnifyBytes<int16_t>(data_buffer_[counter++], data_buffer_[counter++]);
    coefficients.MD = common::UnifyBytes<int16_t>(data_buffer_[counter++], data_buffer_[counter++]);
}

void BMP180::SetOSS(domain::MeasureDiscretion oss)
{
    oss_ = oss;
}

void BMP180::ReadData()
{
    GetTemperature();
    GetPressure();
    if (temperature_raw != 0 && pressure_raw != 0)
    {
        ExecuteCalculation();
    }
    else
    {
        temperature_raw = pressure_raw = 0;
        temperature_ = pressure_ = 0.;
    }
    Flush();
}

float BMP180::temperature()
{
    return temperature_;
}
float BMP180::pressure()
{
    return pressure_;
}

void BMP180::Flush()
{
    data_buffer_[0] = 0xB6;
    write_register(REGISTERS::SOFT_RESET, 1);
}

void BMP180::Init()
{
    GetCoefficients();
}

uint8_t BMP180::GetOssIndex() const
{
    if (oss_ == domain::MeasureDiscretion::x1)
    {
        return 0u;
    }
    else if (oss_ == domain::MeasureDiscretion::x2)
    {
        return 1u;
    }
    else if (oss_ == domain::MeasureDiscretion::x4)
    {
        return 2u;
    }
    else
    {
        return 3u;
    }
}

void BMP180::SendMeasureCommand(domain::MeasureCommand command)
{
    domain::MeasureDiscretion oss = oss_;
    if (command == domain::MeasureCommand::Temperature)
    {
        oss = domain::MeasureDiscretion::x1;
    }
    data_buffer_[0] =
        domain::MeasureControl{
            oss,
            command,
        }
            .Pack();

    write_register(REGISTERS::MEASUREMENT_CTRL, 1u);
}

bool BMP180::ReadMeasureFlag()
{
    read_register(REGISTERS::MEASUREMENT_CTRL, 1);
    return ((data_buffer_[0] >> 5) & 0x01) == 0x00;
}

bool BMP180::ExecuteMeasure(domain::MeasureCommand command, uint8_t attempts = 4u)
{
    SendMeasureCommand(command);
    bool measure_done = false;
    uint8_t attempt_count = 1u;
    while (measure_done == false)
    {
        sleep_ms(5u);
        measure_done = ReadMeasureFlag();
        if (attempt_count > attempts)
        {
            return false;
        }
        attempt_count++;
    }
    return true;
}

void BMP180::GetTemperature()
{
    bool temp_flag = ExecuteMeasure(domain::MeasureCommand::Temperature);
    if (temp_flag == true)
    {
        read_register(REGISTERS::OUT_MSB, 2);
        long t_raw_msb = static_cast<long>(data_buffer_[0]) << 8u;
        temperature_raw = ((static_cast<long>(data_buffer_[0]) << 8u) + (static_cast<long>(data_buffer_[1]) && 0xff));
    }
    else
    {
        temperature_raw = 0;
    }
}

void BMP180::GetPressure()
{
    bool pres_flag = ExecuteMeasure(domain::MeasureCommand::Pressure);
    if (pres_flag == true)
    {
        read_register(REGISTERS::OUT_MSB, 3);
        pressure_raw = (((static_cast<long>(data_buffer_[0]) << 16u)) + ((static_cast<long>(data_buffer_[1]) << 8u)) +
                        static_cast<long>(data_buffer_[2])) >>
                       (8u - GetOssIndex());
    }
    else
    {
        pressure_raw = 0;
    }
}

void BMP180::ExecuteCalculation()
{
    uint8_t oss = GetOssIndex();
    long X1, X2, B5, T;
    long B6, X3, B3;
    unsigned long B4, B7;

    /*Calculate temperature*/
    X1 = ((temperature_raw - coefficients.AC6) * coefficients.AC5) >> 15;
    X2 = (coefficients.MC << 11) / (X1 + coefficients.MD);
    B5 = X1 + X2;
    T = (B5 + 8) >> 4;
    temperature_ = (double)T / 10;

    /*Calculate pressure*/
    B6 = B5 - 4000;
    X1 = (coefficients.B2 * ((B6 * B6) >> 12)) >> 11;
    X2 = (coefficients.AC2 * B6) >> 11;
    X3 = X1 + X2;
    B3 = (((coefficients.AC1 * 4 + X3) << oss) + 2) >> 2;
    X1 = (coefficients.AC3 * B6) >> 13;
    X2 = (coefficients.B1 * ((B6 * B6) >> 12)) >> 16;
    X3 = ((X1 + X2) + 2) >> 2;
    B4 = (coefficients.AC4 * (unsigned long)(X3 + 32768)) >> 15;
    B7 = ((unsigned long)pressure_raw - B3) * (50000 >> oss);
    if (B7 < 0x80000000)
        pressure_raw = (B7 * 2) / B4;
    else
        pressure_raw = (B7 / B4) * 2;
    X1 = (pressure_raw >> 8) * (pressure_raw >> 8);
    X1 = (X1 * 3038) >> 16;
    X2 = (-7357 * (pressure_raw)) >> 16;
    pressure_raw = pressure_raw + ((X1 + X2 + 3791) >> 4);
    pressure_ = static_cast<unsigned>(((float)pressure_raw) * 0.7500615f / 100.f);
}
} // namespace BMP180
