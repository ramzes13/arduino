
// /* Example sketch to control a 28BYJ-48 stepper motor with ULN2003 driver board and Arduino UNO. More info: https://www.makerguides.com */
// // Include the Arduino Stepper.h library:
// // #include <Stepper.h>
// #include <AccelStepper.h>
// #include <MultiStepper.h>

// void setup() {
//   // put your setup code here, to run once:

// }

// void loop() {
//   // put your main code here, to run repeatedly:

// }
// // Define number of steps per rotation:
// const int stepsPerRevolution = 2048;
// // Wiring:
// // Pin 8 to IN1 on the ULN2003 driver
// // Pin 9 to IN2 on the ULN2003 driver
// // Pin 10 to IN3 on the ULN2003 driver
// // Pin 11 to IN4 on the ULN2003 driver
// // Create stepper object called 'myStepper', note the pin order:
// Stepper myStepper(stepsPerRevolution, 14, 12, 13, 15);
// void setup() {
//   // Set the speed to 5 rpm:
//   myStepper.setSpeed(10);
  
//   // Begin Serial communication at a baud rate of 9600:
//   Serial.begin(9600);
// }
// void loop() {
//   // Step one revolution in one direction:
//   Serial.println("clockwise");
//   myStepper.step(stepsPerRevolution);
//   delay(10);
  
//   // Step one revolution in the other direction:
//   Serial.println("counterclockwise");
//   myStepper.step(-stepsPerRevolution);
//   delay(10);
// }


// #include <AccelStepper.h>
// AccelStepper stepper(AccelStepper::FULL4WIRE, 14, 12, 13, 15); // Defaults to AccelStepper::FULL4WIRE (4 pins) on 2, 3, 4, 5
// void setup()
// {  
//    stepper.setMaxSpeed(1000);
//    stepper.setSpeed(70);        
// }
// void loop()
// {  
//    stepper.runSpeed();
// }
