/*
 * IRremote: IRrecvDemo - demonstrates receiving IR codes with IRrecv
 * An IR detector/demodulator must be connected to the input RECV_PIN.
 * Version 0.1 July, 2009
 * Copyright 2009 Ken Shirriff
 * http://arcfn.com
 */

#include <IRremote.h>

int RECV_PIN = 11;

IRrecv irrecv(RECV_PIN);

decode_results results;

void setup()
{
  Serial.begin(9600);
  // In case the interrupt driver crashes on setup, give a clue
  // to the user what's going on.
  Serial.println("Enabling IRin");
  irrecv.enableIRIn(); // Start the receiver
  Serial.println("Enabled IRin");
}

void loop() {
  if (irrecv.decode(&results)) {
    if (results.decode_type == NEC) {
      Serial.print("NEC: ");
    } else if (results.decode_type == SONY) {
      Serial.print("SONY: ");
    } else if (results.decode_type == RC5) {
      Serial.print("RC5: ");
    } else if (results.decode_type == RC6) {
      Serial.print("RC6: ");
    } else if (results.decode_type == UNKNOWN) {
      Serial.print("UNKNOWN: ");
    }
    Serial.println(results.value, HEX);
    Serial.println(results;
    Serial.println("Begin");
    for(int i = 0; i < results.rawlen; i++)
    {
      Serial.print(results.rawbuf[i]);
      Serial.print(", ");
    }
    Serial.println("\nEnd");
    irrecv.resume(); // Receive the next value
  }
  delay(100);



  // irsend.sendNEC(IRcode, numBits);
// Send a code in NEC format.

// irsend.sendSony(IRcode, numBits);
// Send a code in Sony format.

// irsend.sendRC5(IRcode, numBits);
// Send a code in RC5 format.

// irsend.sendRC6(IRcode, numBits);
// Send a code in RC6

// irsend.sendRaw(rawbuf, rawlen, frequency);
}