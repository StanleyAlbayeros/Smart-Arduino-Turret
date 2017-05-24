#ifndef Display_h
#define Display_h

#include "Arduino.h"
#include <Adafruit_GFX.h>
#include <Adafruit_NeoPixel.h>
#include <Adafruit_NeoMatrix.h>
#include <LiquidCrystal.h>



/*to be able to use either a 16x2 lcd display with an I2C controller or a
   8x8 WS2812B LED matrix, choose either one of the two defines
*/

#define neoPixelMatrix
//#define LMC1602

class Display {

  public:

#ifdef neoPixelMatrix
    Display();
#endif

#ifdef LMC1602
    Display(uint8_t SDAPin, uint8_t SCLPin);
#endif

    void displayRange(uint8_t range);
    void Display::preparing();
    void Display::shooting();
    void Display::scanning();
    void Display::detected();


  private:
#ifdef neoPixelMatrix
    uint8_t neomatrixPin = 6;
    Adafruit_NeoMatrix myMatrix;

    struct RGB {
      byte r;
      byte g;
      byte b;
    };

    const uint16_t colors[4] = {
      myMatrix.Color(255, 0, 50), myMatrix.Color(50, 0, 255), myMatrix.Color(255, 0, 0), myMatrix.Color(255,255,255)
    };
#endif
#ifdef LMC1602

#endif


};

#endif
