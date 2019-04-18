#include "SSD1306Wire.h"

SSD1306Wire display(0x3c, D3, D5);

// void prinToScreenNative(String str)
// {
//   display.drawString(str);
//   // Print to the screen
//   display.println(str);
//   // Draw it to the internal screen buffer
//   display.drawLogBuffer(0, 0);
//   // Display it on the screen
//   display.display();
//   delay(500);
// }

void prinToScreen(String str)
{
  display.clear();
  // Print to the screen
  display.println(str);
  // Draw it to the internal screen buffer
  display.drawLogBuffer(0, 0);
  // Display it on the screen
  display.display();
  delay(500);
}

void printBuffer(void)
{
  // Some test data
  const char *test[] = {
      "Hello",
      "World",
      "----",
      "Show off",
      "how",
      "the log buffer",
      "is",
      "working.",
      "Even",
      "scrolling is",
      "working"};

  for (uint8_t i = 0; i < 11; i++)
  {
    display.clear();
    // Print to the screen
    display.println(test[i]);
    // Draw it to the internal screen buffer
    display.drawLogBuffer(0, 0);
    // Display it on the screen
    display.display();
    delay(500);
  }
}

void setup()
{
  Serial.begin(9600);
  // Serial.setDebugOutput(true);
  display.init();
  display.setContrast(255);
  display.setLogBuffer(4, 14);
  display.setFont(ArialMT_Plain_16);

  // prinToScreen("aaaaaaaaaaaa");
  // printBuffer();
  delay(1000);
  // display.clear();
}

void loop()
{
  while (Serial.available() > 0)
  {
    String str = Serial.readString();
    if (str)
    {
      Serial.println("identified");
      // char *tmp = str.toCharArray();
      prinToScreen(str);
      delay(500);
    }
  }
}