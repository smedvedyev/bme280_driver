#include <Arduino.h>
#include <Wire.h>
#define SLAVE_ADDRESS 0x50
#define INA 21
#define INB 22
#define MIN 23
#define MAX 24

void WriteToSlave(int address, int message){
  Wire.beginTransmission(SLAVE_ADDRESS);
  Wire.write(address);
  Wire.write(message);
  Wire.endTransmission();

}
void ReadFromSlave(int address){
  Wire.beginTransmission(SLAVE_ADDRESS);
  Wire.write(address);
  Wire.endTransmission();
  Wire.requestFrom(SLAVE_ADDRESS, 1);
  int response = Wire.read();
  Serial.println(response);
}
void setup(){
  Wire.begin();
  Serial.begin(9600);
}
void loop(){
  WriteToSlave(INA, 4);
  WriteToSlave(INB, 12);
  ReadFromSlave(MIN);
  ReadFromSlave(MAX);
  delay(500);
}