// Wire Slave Receiver
// by Nicholas Zambetti <http://www.zambetti.com>

// Demonstrates use of the Wire library
// Receives data as an I2C/TWI slave device
// Refer to the "Wire Master Writer" example for use with this

// Created 29 March 2006

// This example code is in the public domain.

#include <Arduino.h>
#include <Wire.h>
#define ADDRESS 0x42
byte response = 0;
void receiveEvent(int howMany) {
  int x = Wire.read();    // receive byte as an integer
  if(x<100){
    response = 4;

  } 
  else{
    response = 2;
  }
  
}

void requestEvent(){
  Wire.write(response);
  Serial.println(response);
}


void setup() {
  Wire.begin(ADDRESS);                // join I2C bus with address #8
  Wire.onReceive(receiveEvent); // register event
  Wire.onRequest(requestEvent); 
  Serial.begin(9600);           // start serial for output
}

void loop() {
  delay(100);
}

// function that executes whenever data is received from master
// this function is registered as an event, see setup()
