
#define potentiometer A0 //10k Variable Resistor
#define bt_F A1          // Clockwise Button
#define bt_S A2          // Stop Button
#define bt_B A3          // Anticlockwise Button

#define in1 14 //Motor  L298 Pin in1
#define in2 12 //Motor  L298 Pin in2
#define in3 13 //Motor  L298 Pin in3
#define in4 15 //Motor  L298 Pin in4

int read_ADC;
int Speed_LCD;
int Speed = 0;
int Cycles = 0;
int StepDelay = 1;
int Step;
int Mode = 1;
const int buttonPin = 16; // the number of the pushbutton pin
int buttonState = 0;      // variable for reading the pushbutton status

void setup()
{
  Serial.begin(9600);
  pinMode(in1, OUTPUT); // declare as output for L298 Pin in1
  pinMode(in2, OUTPUT); // declare as output for L298 Pin in2
  pinMode(in3, OUTPUT); // declare as output for L298 Pin in3
  pinMode(in4, OUTPUT); // declare as output for L298 Pin in4
  pinMode(buttonPin, INPUT);

  delay(1000); // Waiting for a while
}
//Speed = 50;
//Mode = 1;
void loop()
{
  if (Serial.available() > 0)
  {
    // read the incoming byte:
    int StepDelayVal = Serial.parseInt();
    if (StepDelayVal > 0)
    {
      StepDelay = StepDelayVal;
      // say what you got:
      Serial.print("I received: ");
      Serial.println(StepDelay, DEC);
    }
  }

  buttonState = digitalRead(buttonPin);

  // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
  if (buttonState == HIGH)
  {
    Cycles++;

    move_forward();
  }
  else
  {
    if (Cycles > 0)
    {
      Cycles--;
      move_backward();
    }
    else
    {
      stop_mottor();
    }
  }
}

void move_forward()
{
  Serial.print("move_forward ");
  Step = Step + 1;
  if (Step > 3)
  {
    Step = 0;
  }
  call_Step(Step);
}

void move_backward()
{
  Serial.print("move_backward ");
  Step = Step - 1;
  if (Step < 0)
  {
    Step = 3;
  }

  call_Step(Step);
}

void stop_mottor()
{
  if (Step != 4)
  {
    Serial.print("stop_mottor ");
    Step = 4;
    call_Step(Step);
  }
}

void call_Step(int i)
{
  Serial.println(Cycles, DEC);
  delay(StepDelay);
  switch (i)
  {
  case 0: // 1010
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
    break;
  case 1: // 0110
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
    break;
  case 2: //0101
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);
    break;
  case 3: //1001
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);
    break;
  case 4: //0000
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    digitalWrite(in3, LOW);
    digitalWrite(in4, LOW);
    break;
  }
}
