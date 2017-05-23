#include "Display.h"

  #ifdef LMC1602
  Display::Display(){
    
  }
  #endif
  
  #ifdef neoPixelMatrix
    Display::Display(uint8_t SDAPin, uint8_t SCLPin): myMatrix(8,8,6, NEO_MATRIX_TOP     + NEO_MATRIX_RIGHT +
                                NEO_MATRIX_COLUMNS + NEO_MATRIX_PROGRESSIVE,
                                NEO_GRB            + NEO_KHZ800){
      myMatrix.begin();
      myMatrix.setBrightness(10);
    }

    
  #endif

  void Display::displayRange(uint8_t range){

    #ifdef neoPixelMatrix
      myMatrix.fillScreen(myMatrix.Color(255,0,255);
      myMatrix.show();
    #endif

    
  }

