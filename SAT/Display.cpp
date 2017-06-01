#include "Display.h"

#ifdef LMC1602
Display::Display(uint8_t SDAPin, uint8_t SCLPin) {

}
#endif

#ifdef neoPixelMatrix
Display::Display(): myMatrix(8, 8, neomatrixPin,
                               NEO_MATRIX_BOTTOM
                               + NEO_MATRIX_RIGHT
                               + NEO_MATRIX_ROWS
                               + NEO_MATRIX_PROGRESSIVE,
                               NEO_GRB + NEO_KHZ800) {
  myMatrix.begin();
  myMatrix.setBrightness(5);
}
#endif

void Display::displayRange(uint8_t range) {

#ifdef neoPixelMatrix
  //cambiar a setbrightness(range) o numero de leds encendidos dependiente de range?

  myMatrix.fillScreen(myMatrix.Color(255, 0, 255));

  myMatrix.show();

#endif

#ifdef LMC1602
  //display first line black squares depending on range
#endif


}

void Display::preparing() {
#ifdef neoPixelMatrix
    for (uint16_t i = 0; i < 8; i++) {
    if (i % 3 == 0) {
      //myMatrix.clear();
    }

    myMatrix.drawLine(i, 0, 7 - i, 7, colors[3]);
    myMatrix.drawLine(7, i, 0, 7 - i, colors[3]);
    myMatrix.show();
    delay(5);
  }
  delay(10);
#endif
}

void Display::shooting() {
#ifdef neoPixelMatrix
  myMatrix.fillScreen(colors[4]);

#endif
}

void Display::scanning() {
#ifdef neoPixelMatrix
  for (uint16_t i = 0; i < 8; i++) {
    if (i % 3 == 0) {
      myMatrix.clear();
    }

    myMatrix.drawLine(i, 0, 7 - i, 7, colors[0]);
    myMatrix.drawLine(7, i, 0, 7 - i, colors[1]);
    myMatrix.show();
    delay(5);
  }
  delay(10);
#endif
}

void Display::detected() {
#ifdef neoPixelMatrix

    for (uint16_t i = 0; i < 8; i++) {
    if (i % 3 == 0) {
      //myMatrix.clear();
    }

    myMatrix.drawLine(i, 0, 7 - i, 7, colors[0]);
    myMatrix.drawLine(7, i, 0, 7 - i, colors[2]);
    myMatrix.show();
    delay(5);
  }
  delay(10);
#endif
}




