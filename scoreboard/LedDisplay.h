#include "LedWrappers.h"
static const int digits[10][7] = {
//   1  2  3  4  5  6  7
    {1, 1, 1, 0, 1, 1, 1}, // zero
    {0, 0, 1, 0, 0, 0, 1}, // one
    {1, 1, 0, 1, 0, 1, 1}, // two
    {0, 1, 1, 1, 0, 1, 1}, // three
    {0, 0, 1, 1, 1, 0, 1}, // four
    {0, 1, 1, 1, 1, 1, 0}, // five
    {1, 1, 1, 1, 1, 1, 0}, // six
    {0, 0, 1, 0, 0, 1, 1}, // seven
    {1, 1, 1, 1, 1, 1, 1}, // eight
    {0, 1, 1, 1, 1, 1, 1}  // nine
};




class LedDisplay {
  public:
    LedDisplay(int pin = D1, int numPixels = 70, bool emulated = false): pin(pin), numPixels(numPixels) {
      brightness = 255;
      lights = emulated? static_cast<LedWrapper*>(new LedEmulator()) : static_cast<LedWrapper*>(new NeoPixelWrapper());
    }

/*
* shows the value on the position given by digitOffset
*example with 4 digits: showDigit(7, 1) -> |0|0|7|0|
*/
    void showDigit(int value, int digitOffset; int color[3] = {100, 100, 100}) {
        int pixelOffset = digitOffset * 35;
        
        if (digit < 0 || digit > 9) {
            Serial.println("illegal argument");
            return;
      }
      for (int pixel = offset; pixel < offset + 35; ++pixel) {
        int segment = (pixel-pixelOffset) / 5;
        bool pixelActive = digits[value][segment];
        if(pixelActive){
            lights->setPixelColor(pixel, color);
        }
        else{
            lights->setPixelColor(pixel, 0);
      }
    }
    void showNumber(int number){
        int numDigits = numPixels / 35;
        for (int i=0; i<numPixels; ++i){
            int digitFactor = pow(10, (numPixels-1-i));
            lights->showDigit(number%digitFactor, i);
        }
        lights->show();
    }


  private:
    int pin;
    int numPixels;
    int brightness;
    LedWrapper* lights;

};
