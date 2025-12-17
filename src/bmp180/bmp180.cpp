#include "bmp180/bmp180.h"
#include "bmp180/bmp180_common.h"
namespace BMP180
{

BMP180::BMP180(i2c_inst_t *i2c) : I2CDevice(i2c, REGISTERS::ADDR)
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
} // namespace BMP180

void BMP180::BMP180::GetTemperature()
{
}

void BMP180::BMP180::GetPressure()
{
}

void BMP180::BMP180::SendMeasureCommand(domain::MeasureCommand command,
                                        domain::MeasureDiscretion discretion = domain::MeasureDiscretion::x1)
{
}
