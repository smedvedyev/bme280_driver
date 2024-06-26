// Wire Master Writer
// by Nicholas Zambetti <http://www.zambetti.com>

// Demonstrates use of the Wire library
// Writes data to an I2C/TWI slave device
// Refer to the "Wire Slave Receiver" example for use with this

// Created 29 March 2006

// This example code is in the public domain.

#include <Arduino.h>
#include <Wire.h>
#define SLAVE_ADDRESS 0x42
void setup()
{
  Wire.begin(); 
  Serial.begin(9600);
}

byte x = 80;
byte response = 0;
void loop()
{
  Wire.beginTransmission(SLAVE_ADDRESS); 
  Wire.write(x);                     
  Wire.endTransmission();                
  Wire.requestFrom(SLAVE_ADDRESS, 8);
  response = Wire.read();
  Serial.println(response);
  x++;
  delay(500);
}
