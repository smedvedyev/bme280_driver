#ifndef ARD_I2C
#define ARD_I2C

#include <Arduino.h>
#include <Wire.h>

#define SLAVE_ADDRESS 0x50
#define INA 21
#define INB 22
#define MIN 23
#define MAX 24
#define MESSAGE_INTERVAL 500

void WriteToSlave(int, int);
void ReadFromSlave(int);
bool MessageInterval(unsigned long);

#endif