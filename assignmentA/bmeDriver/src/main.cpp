#include <Arduino.h>
#include <Wire.h>
#include "BME280.h"

void setup()
{
  Wire.begin();
  Serial.begin(9600);
  Serial.println(BME280_GetID());
  BME280_Reset();
  // Setting normal oversampling for humidity
  BME280_CtrlHum(0x01);
  // Setting normal oversampling for measurements
  BME280_CtrlMeas(0x27);
}

void loop()
{
  Serial.print("Temperature: ");
  Serial.print(BME280_ReadTemperature() * 0.01);
  Serial.println(" °C");
  Serial.print("Pressure: ");
  Serial.print(BME280_ReadPressure() / (256.0*100));
  Serial.println(" hPa");
  Serial.print("Humidity: ");
  Serial.print(BME280_ReadHumidity() / 1024.00);
  Serial.println(" %");
  Serial.println();

  Serial.println(BME280_CtrlHum(),HEX);
  Serial.println(BME280_CtrlMeas(), HEX);

  delay(1000);
}