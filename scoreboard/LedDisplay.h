#pragma once
#include "LedWrappers.h"
#include <map>
#include "Color.h"
static const bool digits[10][7] = {
//   1  2  3  4  5  6  7  (segments)
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
	int pin;
	int numPixels;
	LedWrapper* lights;
public:
    LedDisplay(int pin = D5, int numPixels = 142, bool emulated = false){
      lights = emulated? static_cast<LedWrapper*>(new LedEmulator()) : static_cast<LedWrapper*>(new NeoPixelWrapper(pin, numPixels));
	}

	void show() {
		lights->show();
	}
	void showDigit(int value, int pixelOffset, Color color = Color()) {
		if (value < 0 || value > 9) {
			Serial.printf("illegal digit: %d\n", value);
			return;
		}
		for (int pixel = 0; pixel < 35; ++pixel) {
			int segment = pixel / 5;
			bool pixelActive = digits[value][segment];
			if (pixelActive) {
				lights->setPixelColor(pixel + pixelOffset, color);
			}
			else {
				lights->setPixelColor(pixel + pixelOffset, Color(0,0,0));
			}
		}
	}
    void showNumber(int number, Color color, int pixelOffset = 0){
		showDigit(number / 10, pixelOffset, color);
		showDigit(number % 10, 35 + pixelOffset, color);
        lights->show();
    }
	void setPixel(int index, Color color) {
		lights->setPixelColor(index, color);
	}

};
