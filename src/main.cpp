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
  Serial.begin(9600);
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

// void setup() {
//   Serial.begin(9600);
//   while (!Serial) {
//     // no op
//   }
//   matrix.begin();
  // int      x, y, hue;
  // float    dx, dy, d;
  // uint8_t  sat, val;
  // uint16_t c;
  //
  // matrix.begin();
  //
  // for(y=0; y < matrix.width(); y++) {
  //   dy = 15.5 - (float)y;
  //   for(x=0; x < matrix.height(); x++) {
  //     dx = 15.5 - (float)x;
  //     d  = dx * dx + dy * dy;
  //     if(d <= (16.5 * 16.5)) { // Inside the circle(ish)?
  //       hue = (int)((atan2(-dy, dx) + PI) * 1536.0 / (PI * 2.0));
  //       d = sqrt(d);
  //       if(d > 15.5) {
  //         // Do a little pseudo anti-aliasing along perimeter
  //         sat = 255;
  //         val = (int)((1.0 - (d - 15.5)) * 255.0 + 0.5);
  //       } else
  //       {
  //         // White at center
  //         sat = (int)(d / 15.5 * 255.0 + 0.5);
  //         val = 255;
  //       }
  //       c = matrix.ColorHSV(hue, sat, val, true);
  //     } else {
  //       c = 0;
  //     }
  //     matrix.drawPixel(x, y, c);
  //   }
  // }
// }
