#include <Arduino.h>
#ifndef BME280_H
#define BME280_H

#define BME_ADDRESS 0x76
#define BME_ID 0xd0
#define BME280_RESET 0xE0
#define BME280_COMPLETE_RESET 0xB6

#define DIG_T1 0x88
#define DIG_T2 0x8A
#define DIG_T3 0x8C
#define DIG_P1 0x8E
#define DIG_P2 0x90
#define DIG_P3 0x92
#define DIG_P4 0x94
#define DIG_P5 0x96
#define DIG_P6 0x98
#define DIG_P7 0x9A
#define DIG_P8 0x9C
#define DIG_P9 0x9E
#define DIG_H1 0xA1
#define DIG_H2 0xE1
#define DIG_H3 0xE3
#define DIG_H4 0xE4
#define DIG_H5 0xE5
#define DIG_H6 0xE7

#define CTRL_HUM 0xF2
#define CTRL_MEAS 0xF4

typedef enum
{
    HUM,
    TEMP,
    PRESS
} Data;

// Returns the Id of bme280 sensor
uint8_t BME280_GetID();

//Reset BME280 sensor
void BME280_Reset();

//Read temperature with all compensations
long BME280_ReadTemperature();

//Read pressure with all compensations
uint32_t BME280_ReadPressure();

//Read humidity with all compensations
uint32_t BME280_ReadHumidity();

//Reads the oversampling of humidity data
uint8_t BME280_CtrlHum();

//Changes the oversampling of humidity data to provided bit mask
void BME280_CtrlHum(uint8_t bitpattern);

//Reads the oversampling of temperature and pressure data
uint8_t BME280_CtrlMeas();

//Changes the oversampling of temperature and pressure data to provided bit mask
void BME280_CtrlMeas(uint8_t bitpattern);

#endif