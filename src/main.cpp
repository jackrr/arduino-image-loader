#include "Arduino.h"
#include <Adafruit_GFX.h>   // Core graphics library
#include <RGBmatrixPanel.h> // Hardware-specific library

#define CLK 8  // MUST be on PORTB! (Use pin 11 on Mega)
#define OE  9
#define LAT 10
#define A   A0
#define B   A1
#define C   A2
#define D   A3

RGBmatrixPanel matrix(A, B, C, D, CLK, LAT, OE, false);
bool unfinished;

void setup() {
  Serial.begin(115200);
  while (!Serial) {
    // no op
  }
  matrix.begin();
  unfinished = false;
}

void processPixel() {
  uint16_t c;
  long x, y, h, s, v;

  x = Serial.parseInt();
  y = Serial.parseInt();
  h = Serial.parseInt();
  s = Serial.parseInt();
  v = Serial.parseInt();

  c = matrix.ColorHSV(h, s, v, true);
  matrix.drawPixel(x, y, c);
}

void loop() {
  while (Serial.available() > 0) {
    if (Serial.read() == '<') {
      processPixel();
    }
  }
}
