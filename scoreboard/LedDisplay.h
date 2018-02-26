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
      lights = emulated? new LedEmulator() : new NeoPixelWrapper();
    }

/*
* shows the value of digit on every LED digit
*/
    void showDigit(int digit) {
      if (digit < 0 || digit > 9) {
        Serial.println("illegal argument");
        return;
      }
      for (int pixel = 0; pixel < numPixels; ++pixel) {
        int segment = pixel / 5;
        segment %= 7;
        bool pixelActive = digits[digit][segment];
        int pixelBrightness = pixelActive ? brightness : 0;
        
        // shift color (red -> green -> blue -> red) after each pixel
        int redval = pixel % 3 == 0 ? pixelBrightness : 0;
        int greenval = pixel % 3 == 1 ? pixelBrightness : 0;
        int blueval = pixel % 3 == 2 ? pixelBrightness : 0;
        lights->setPixelColor(pixel, redval, greenval, blueval);
      }
      lights->show();
    }


  private:
    int pin;
    int numPixels;
    int brightness;
    LedWrapper* lights;

};
