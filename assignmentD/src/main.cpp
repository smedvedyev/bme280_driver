#include <Arduino.h>
#include "ard_i2c.h"
#include "BME280.h"
unsigned long startTime;
void setup()
{
  Wire.begin();
  Serial.begin(9600);
  startTime = millis();
  BME280_Reset();
  BME280_CtrlHum(0x01);
  BME280_CtrlMeas(0x27);
}

void loop()
{
  if (MessageInterval(startTime))
  {
    startTime = millis();
    WriteToSlave(INA, 60);
    WriteToSlave(INB, 100);
    Serial.print("Min: ");
    Serial.println(ReadFromSlave(MIN));
    Serial.print("Max: ");
    Serial.println(ReadFromSlave(MAX));

    Serial.print("Temperature: ");
    Serial.print(BME280_ReadTemperature() * 0.01);
    Serial.println(" °C");
    Serial.print("Pressure: ");
    Serial.print(BME280_ReadPressure() / (256.0 * 100));
    Serial.println(" hPa");
    Serial.print("Humidity: ");
    Serial.print(BME280_ReadHumidity() / 1024.00);
    Serial.println(" %");
    Serial.println();
  }
}
