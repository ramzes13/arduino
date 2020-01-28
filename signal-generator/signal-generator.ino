#include "Arduino.h"
#include "HardwareSerial.h"
/*
  ReadAnalogVoltage

  Reads an analog input on pin 0, converts it to voltage, and prints the result to the Serial Monitor.
  Graphical representation is available using Serial Plotter (Tools > Serial Plotter menu).
  Attach the center pin of a potentiometer to pin A0, and the outside pins to +5V and ground.

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/ReadAnalogVoltage
*/
const uint8_t pin = 5;
bool up = true;
// the setup routine runs once when you press reset:
void setup()
{
  pinMode(pin, OUTPUT);
  pinMode(pin, HIGH);
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
}

// the loop routine runs over and over again forever:
void loop()
{
  // Serial.println("up" + up);
  // delay(1);
  if (up)
  {
    digitalWrite(pin, LOW);
    up = false;
  }
  else
  {
    digitalWrite(pin, HIGH);
    up = true;
  }
}