#ifndef Display_h
#define Display_h

#include "Arduino.h"
#include <Adafruit_GFX.h>
#include <Adafruit_NeoPixel.h>
#include <Adafruit_NeoMatrix.h>
#include <LiquidCrystal.h>


class Display {

  public:

    Display();

    void displayRange(uint8_t range);
    void Display::preparing();
    void Display::shooting();
    void Display::scanning();
    void Display::detected();


  private:
    uint8_t neomatrixPin = 6;
    Adafruit_NeoMatrix myMatrix;

    struct RGB {
      byte r;
      byte g;
      byte b;
    };

    const uint16_t colors[4] = {
      myMatrix.Color(255, 0, 50), myMatrix.Color(50, 0, 255), myMatrix.Color(255, 0, 0), myMatrix.Color(255, 255, 255)
    };
};

#endif

