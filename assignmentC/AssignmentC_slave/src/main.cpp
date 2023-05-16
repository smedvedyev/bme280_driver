#include <Arduino.h>
#include <Wire.h>
#define THIS_ADDRESS 0x50
#define INA 21
#define INB 22
#define MIN 23
#define MAX 24
#define min(a,b) a<b ? a : b
#define max(a,b) a>b ? a : b

int a = 0;
int b = 0;


void ReceiveFunction(int num)
{
  int reg = Wire.read();
  int val = Wire.read();
  Wire.write(val);

  switch (reg)
  {
  case INA:
    a = val;
    break;
  case INB:
    b = val;
    break;
  default:
    break;
  }
}

void RequestFunc()
{
  int response = 0;
  int reg = Wire.read();
  switch (reg)
  {
  case INA:
    response = a;
    break;
  case INB:
    response = b;
    break;
  case MAX:
    response = min(a,b);
    break;
  case MIN:
    response = max(a,b);
    break;
  }
  
}

void setup()
{
  Wire.begin(THIS_ADDRESS);
  Wire.onReceive(ReceiveFunction);
  Wire.onRequest(RequestFunc);
  Serial.begin(9600);
}
void loop()
{
}