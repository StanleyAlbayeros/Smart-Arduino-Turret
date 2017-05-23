#ifndef Display_h
#define Display_h

#include "Arduino.h"
#include <Adafruit_GFX.h>
#include <Adafruit_NeoPixel.h>
#include <Adafruit_NeoMatrix.h>


/*to be able to use either a 16x2 lcd display with an I2C controller or a 
 * 8x8 WS2812B LED matrix, choose either one of the two defines 
 */

//#define neoPixelMatrix
#define LMC1602
   

class Display {

  public:

    #ifdef neoPixelMatrix
      Display(uint8_t SDAPin, uint8_t SCLPin);
    #endif

    #ifdef LMC1602
      Display();
    #endif
  private:
  
    #ifdef neoPixelMatrix
      Adafruit_NeoMatrix myMatrix;
    #endif
    
};

#endif
