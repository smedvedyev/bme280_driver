#include "ard_i2c.h"
unsigned long startTime;
void setup()
{
  Wire.begin();
  Serial.begin(9600);
  startTime = millis();
}
void loop()
{
  if (MessageInterval(startTime))
  {
    startTime = millis();
    WriteToSlave(INA, 4);
    WriteToSlave(INB, 12);
    Serial.print("Min: ");
    ReadFromSlave(MIN);
    Serial.print("Max: ");
    ReadFromSlave(MAX);
  }
}