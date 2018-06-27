/*
 Controlling a servo position using a potentiometer (variable resistor)
 by Michal Rinott <http://people.interaction-ivrea.it/m.rinott>

 modified on 8 Nov 2013
 by Scott Fitzgerald
 http://www.arduino.cc/en/Tutorial/Knob
*/

#include <Servo.h>

Servo myservo; // create servo object to control a servo

int potpin = 0; // analog pin used to connect the potentiometer
int val;        // variable to read the value from the analog pin
const int buttonPin = 2;

int buttonState = 0;
int direction = 1;

void setup()
{
  Serial.begin(9600);
  pinMode(buttonPin, INPUT);
  val = 0;
  myservo.attach(9); // attaches the servo on pin 9 to the servo object
}

void loop()
{
  buttonState = digitalRead(buttonPin);

  if (buttonState == HIGH)
  {
    val += 5 * direction;
    myservo.write(val); // sets the servo position according to the scaled value
    if (val > 180)
    {
      direction = -1;
    }
    if (val < 0)
    {
      direction = 1;
    }
  }
  Serial.print(val);
  Serial.print(direction);
  Serial.print('\n');
  delay(2); // waits for the servo to get there
}