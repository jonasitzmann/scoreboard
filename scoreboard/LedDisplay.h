#include "LedWrappers.h"
#include <map>
#include "Color.h"
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
    LedDisplay(int pin = D1, int numPixels = 70, bool emulated = false){
      lights = emulated? static_cast<LedWrapper*>(new LedEmulator()) : static_cast<LedWrapper*>(new NeoPixelWrapper(pin, numPixels));
    }

/*
* shows the value on the position given by digitOffset
*example with 4 digits: showDigit(7, 1) -> |0|0|7|0|
*/
	void showDigit(int value, int digitOffset, Color color = WHITE) {
		int pixelOffset = digitOffset * 35;
		if (value < 0 || value > 9) {
			Serial.println("illegal argument");
			return;
		}
		for (int pixel = 0; pixel < 35; ++pixel) {
			int segment = pixel / 5;
			bool pixelActive = digits[value][segment];
			if (pixelActive) {
				lights->setPixelColor(pixel + pixelOffset, color);
			}
			else {
				lights->setPixelColor(pixel + pixelOffset, BLACK);
			}
		}
	}
    void showNumber(int number, Color color){

		showDigit(number / 10, 0, color);
		showDigit(number % 10, 1, color);
        lights->show();
    }


  private:
    int pin;
    int numPixels;
    LedWrapper* lights;

};
