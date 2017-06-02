#include "Display.h"


Display::Display(): myMatrix(8, 8, neomatrixPin,
                               NEO_MATRIX_BOTTOM
                               + NEO_MATRIX_RIGHT
                               + NEO_MATRIX_ROWS
                               + NEO_MATRIX_PROGRESSIVE,
                               NEO_GRB + NEO_KHZ800) {
  myMatrix.begin();
  myMatrix.setBrightness(5);
}
void Display::displayRange(uint8_t range) {
  //cambiar a setbrightness(range) o numero de leds encendidos dependiente de range?

  myMatrix.fillScreen(myMatrix.Color(255, 0, 255));

  myMatrix.show();
}

void Display::preparing() {
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
}

void Display::shooting() {
  myMatrix.fillScreen(colors[4]);
}

void Display::scanning() {
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
}

void Display::detected() {
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
}




