#ifndef ARD_I2C
#define ARD_I2C

#include <Arduino.h>
#include <Wire.h>

#define SLAVE_ADDRESS 0x50
#define INA 21
#define INB 22
#define MIN 23
#define MAX 24
#define MESSAGE_INTERVAL 1000

//Writes to slave's registers to change values
void WriteToSlave(int, int);
//Requests and receives needed data from the slave
int ReadFromSlave(int);
//Timer for sending and requesting data from slave devices
bool MessageInterval(unsigned long);

#endif