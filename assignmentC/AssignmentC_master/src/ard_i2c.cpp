#include "ard_i2c.h"

void WriteToSlave(int address, int message)
{
    Wire.beginTransmission(SLAVE_ADDRESS);
    Wire.write(address);
    Wire.write(message);
    Wire.endTransmission();
}
void ReadFromSlave(int address)
{
    Wire.beginTransmission(SLAVE_ADDRESS);
    Wire.write(address);
    Wire.endTransmission();
    Wire.requestFrom(SLAVE_ADDRESS, 1);
    int response = Wire.read();
    Serial.println(response);
}
bool MessageInterval(unsigned long start){
    return (millis()- start) > MESSAGE_INTERVAL;
}
