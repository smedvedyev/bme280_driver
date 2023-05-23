#include <Arduino.h>
#include <Wire.h>
#include "BME280.h"

//IMPORTANT: All magic numbers are provided by datasheets

uint8_t BME280_GetID()
{
    Wire.beginTransmission(BME_ADDRESS);
    Wire.write(BME_ID);
    Wire.endTransmission();
    Wire.requestFrom(BME_ADDRESS, 1);
    uint8_t id = Wire.read();
    return id;
}

void BME280_Reset()
{
    Wire.beginTransmission(BME_ADDRESS); // address
    Wire.write(BME280_RESET);            // reset the BME
    Wire.write(BME280_COMPLETE_RESET);   // complete reset
    Wire.endTransmission();
    delay(100);
}

uint32_t ReadAll(Data type)
{
    Wire.beginTransmission(BME_ADDRESS);
    Wire.write(0xf7);
    Wire.endTransmission(false);
    delay(50);
    Wire.requestFrom(BME_ADDRESS, 8);
    uint32_t press_msb = Wire.read();
    uint32_t press_lsb = Wire.read();
    uint32_t press_xlsb = Wire.read();

    uint32_t temp_msb = Wire.read();
    uint32_t temp_lsb = Wire.read();
    uint32_t temp_xlsb = Wire.read();

    uint32_t hum_msb = Wire.read();
    uint32_t hum_lsb = Wire.read();

    uint32_t pressure = (press_msb << 12) | (press_lsb << 4) | (press_xlsb >> 4);
    uint32_t temperature = (temp_msb << 12) | (temp_lsb << 4) | (temp_xlsb >> 4);
    uint32_t humidity = (hum_msb << 8) | hum_lsb;

    switch (type)
    {
    case HUM:
        return humidity;
        break;
    case TEMP:
        return temperature;
        break;
    case PRESS:
        return pressure;
        break;
    default:
        return 0;
        break;
    }
}
uint16_t GetTwoBytes(uint8_t address)
{
    Wire.beginTransmission(BME_ADDRESS);
    Wire.write(address);
    Wire.endTransmission();
    delay(50);
    Wire.requestFrom(BME_ADDRESS, 2);
    long byte = Wire.read();
    byte |= (Wire.read() << 8);
    return byte;
}

uint16_t GetTwoBytesHum(uint8_t address, int type)
{
    Wire.beginTransmission(BME_ADDRESS);
    Wire.write(address);
    Wire.endTransmission();
    delay(50);
    Wire.requestFrom(BME_ADDRESS, 2);
    long byte;
    switch (type)
    {
    case 0:
        byte = Wire.read() << 4;
        byte |= (Wire.read() >> 4) << 4;
        break;
    case 1:
        byte = (Wire.read() >> 4) << 4;
        byte |= Wire.read();
        break;
    }
    return byte;
}

long GetOneByte(uint8_t address)
{
    Wire.beginTransmission(BME_ADDRESS);
    Wire.write(address);
    Wire.endTransmission();
    delay(50);
    Wire.requestFrom(BME_ADDRESS, 1);
    return Wire.read();
}
int32_t finalTemp;

long BME280_ReadTemperature()
{
    uint32_t rawTemp = ReadAll(TEMP);
    int32_t var1, var2, T;
    unsigned int dig_T1 = GetTwoBytes(DIG_T1);
    int dig_T2 = GetTwoBytes(DIG_T2);
    int dig_T3 = GetTwoBytes(DIG_T3);
    var1 = ((((rawTemp >> 3) - ((int32_t)dig_T1 << 1))) * ((int32_t)dig_T2)) >> 11;
    var2 = (((((rawTemp >> 4) - ((int32_t)dig_T1)) * ((rawTemp >> 4) - ((int32_t)dig_T1))) >> 12) * ((int32_t)dig_T3)) >> 14;
    finalTemp = var1 + var2;
    T = (finalTemp * 5 + 128) >> 8;
    return T;
}

uint32_t BME280_ReadPressure()
{
    uint32_t rawPress = ReadAll(PRESS);
    int64_t var1, var2, p;
    unsigned long dig_P1 = GetTwoBytes(DIG_P1);
    short dig_P2 = GetTwoBytes(DIG_P2);
    short dig_P3 = GetTwoBytes(DIG_P3);
    short dig_P4 = GetTwoBytes(DIG_P4);
    short dig_P5 = GetTwoBytes(DIG_P5);
    short dig_P6 = GetTwoBytes(DIG_P6);
    short dig_P7 = GetTwoBytes(DIG_P7);
    short dig_P8 = GetTwoBytes(DIG_P8);
    short dig_P9 = GetTwoBytes(DIG_P9);

    var1 = (finalTemp)-128000;
    var2 = var1 * var1 * (int64_t)dig_P6;
    var2 = var2 + ((var1 * (int64_t)dig_P5) << 17);
    var2 = var2 + ((int64_t)dig_P4 << 35);
    var1 = ((var1 * var1 * (int64_t)dig_P3) >> 8) + ((var1 * (int64_t)dig_P2) << 12);
    var1 = (((((int64_t)1 << 47) + var1)) * ((int64_t)dig_P1)) >> 33;
    if (var1 == 0)
    {
        return 0; // avoid exception caused by division by zero
    }
    p = 1048576 - rawPress;
    p = (((p << 31) - var2) * 3125) / var1;
    var1 = (((int64_t)dig_P9) * (p >> 13) * (p >> 13)) >> 25;
    var2 = (((int64_t)dig_P8) * p) >> 19;
    p = ((p + var1 + var2) >> 8) + (((int64_t)dig_P7) << 4);
    return (uint32_t)p;
}

uint32_t BME280_ReadHumidity()
{
    int32_t rawHum = ReadAll(HUM);
    int32_t v_x1_u32r;

    unsigned char dig_H1 = GetOneByte(DIG_H1);
    short dig_H2 = GetTwoBytes(DIG_H2);
    unsigned char dig_H3 = GetOneByte(DIG_H3);
    short dig_H4 = GetTwoBytesHum(DIG_H4, 0);
    short dig_H5 = GetTwoBytesHum(DIG_H5, 1);
    char dig_H6 = GetOneByte(DIG_H6);

    v_x1_u32r = (finalTemp - ((int32_t)76800));
    v_x1_u32r = (((((rawHum << 14) - (((int32_t)dig_H4) << 20) - (((int32_t)dig_H5) * v_x1_u32r)) + ((int32_t)16384)) >> 15) * (((((((v_x1_u32r * ((int32_t)dig_H6)) >> 10) * (((v_x1_u32r * ((int32_t)dig_H3)) >> 11) + ((int32_t)32768))) >> 10) + ((int32_t)2097152)) * ((int32_t)dig_H2) + 8192) >> 14));
    v_x1_u32r = (v_x1_u32r - (((((v_x1_u32r >> 15) * (v_x1_u32r >> 15)) >> 7) * ((int32_t)dig_H1)) >> 4));
    v_x1_u32r = (v_x1_u32r < 0 ? 0 : v_x1_u32r);
    v_x1_u32r = (v_x1_u32r > 419430400 ? 419430400 : v_x1_u32r);
    return (uint32_t)(v_x1_u32r >> 12);
}

uint8_t BME280_CtrlHum(){
    Wire.beginTransmission(BME_ADDRESS);
    Wire.write(CTRL_HUM);
    Wire.endTransmission();
    delay(50);
    Wire.requestFrom(BME_ADDRESS,1);
    return Wire.read();
}

void BME280_CtrlHum(uint8_t bitpattern){
    Wire.beginTransmission(BME_ADDRESS);
    Wire.write(CTRL_HUM);
    Wire.write(bitpattern);
    Wire.endTransmission();
}

uint8_t BME280_CtrlMeas(){
    Wire.beginTransmission(BME_ADDRESS);
    Wire.write(CTRL_MEAS);
    Wire.endTransmission();
    delay(50);
    Wire.requestFrom(BME_ADDRESS,1);
    return Wire.read();

}

void BME280_CtrlMeas(uint8_t bitpattern){
    Wire.beginTransmission(BME_ADDRESS);
    Wire.write(CTRL_MEAS);
    Wire.write(bitpattern);
    Wire.endTransmission();

}


