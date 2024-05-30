#include <Arduino.h>
#include <Wire.h>
#define THIS_ADDRESS 0x50
#define INA 21
#define INB 22
#define MIN 23
#define MAX 24

int a = 0;
int b = 0;
int reg = 0;

//Executes whenever something is received from master
void ReceiveFunction(int num)
{
  reg = Wire.read();
  int val = Wire.read();
  switch (reg)
  {
  case INA:
    a = val;
    Serial.println(a);

    break;
  case INB:
    b = val;
    Serial.println(b);

    break;
  default:
    break;
  }
}

//Executes whenever master requests data from the address mentioned in ReceivedFunction()
void RequestFunc()
{
  int response = 0;
  switch (reg)
  {
  case INA:
    response = a;
    break;
  case INB:
    response = b;
    break;
  case MAX:
    response = max(a,b);
    break;
  case MIN:
    response = min(a,b);
    break;
  }
  Wire.write(response);
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