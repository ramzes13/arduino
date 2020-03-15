// High-accuracy square wave generator
// based on ESP8266
// with runtime adjustable frequency, PWM width and offset
// Output wave at pin 5 (configurable from 0 to 15, but not 16)
// by James Swineson <github@public.swineson.me>, 2017-10
// https://gist.github.com/Jamesits/92394675c0fe786467b26f90e95d3904
// See https://blog.swineson.me/implementation-of-6mbps-high-speed-io-on-esp8266-arduino-ide/
// for more information (article in Chinese)
// Arduino UNO version: https://gist.github.com/Jamesits/8d164818946a65d0cafcd6203e3e5049

#include <Esp.h>
#include <esp8266_peri.h>
#include <eagle_soc.h>
#define WDT_CTL 0x60000900
#define WDT_CTL_ENABLE (BIT(0))

// Configurable from 0 to 15; 16 not available
// Please refer to your breakout board datasheet for pin mapping
// WARNING: some pins are used internally for connecting the ESP to ROM chip;
// DO NOT USE THEM or your ESP will be bricked
#define PINOUT 5

double freq;   // Hz
double offset; // percent (0.0 to 1.0)
double width;  // percent (0.0 to 1.0)

// unit: microsecond
unsigned long cycle_time;
unsigned long raising_edge;
unsigned long falling_edge;
unsigned long prev_micros;

// compare 2 unsigned value
// true if X > Y while for all possible (X, Y), X - Y < Z
#define TIME_CMP(X, Y, Z) (((X) - (Y)) < (Z))

inline void setHigh()
{
  GPOS = (1 << PINOUT);
}

inline void setLow()
{
  GPOC = (1 << PINOUT);
}

void setup()
{
  // disable hardware watchdog
  CLEAR_PERI_REG_MASK(WDT_CTL, WDT_CTL_ENABLE);
  // disable software watchdog
  ESP.wdtDisable();
  // set IO pin mode
  pinMode(PINOUT, OUTPUT);

  // calculate arguments
  freq = 125000;
  width = 0.5;
  offset = 0;

  cycle_time = 1000000 / freq;
  raising_edge = (unsigned long)(offset * cycle_time) % cycle_time;
  falling_edge = (unsigned long)((offset + width) * cycle_time) % cycle_time;

  prev_micros = micros();
}

void loop()
{
  if (width + offset < 1)
  {
    // raising edge should appear earlier
    while (TIME_CMP(micros(), prev_micros + raising_edge, cycle_time))
      ;
    setHigh();
    while (TIME_CMP(micros(), prev_micros + falling_edge, cycle_time))
      ;
    setLow();
  }
  else
  {
    // falling edge should appear earlier
    while (TIME_CMP(micros(), prev_micros + falling_edge, cycle_time))
      ;
    setLow();
    while (TIME_CMP(micros(), prev_micros + raising_edge, cycle_time))
      ;
    setHigh();
  }
  prev_micros += cycle_time;
}