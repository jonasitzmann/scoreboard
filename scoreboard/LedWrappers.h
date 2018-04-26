#include <Adafruit_NeoPixel.h>
#include "Color.h"
class LedWrapper{
  public:
  virtual void setPixelColor(int index, Color color) = 0;
  virtual void show() = 0;
};

/*
* Wrapper for the Adafruit_NeoPixel library.
* Forwards commands to Adafruit_NeoPixel instance
*/
class NeoPixelWrapper: public LedWrapper{
  public:
  NeoPixelWrapper(int pin = D5, int numPixels = 142): pin(pin), numPixels(numPixels){
    lights = * new Adafruit_NeoPixel(numPixels, pin,
                 /*suitable pixel flags for our LED Strip*/NEO_GRB + NEO_KHZ800
               );
    lights.begin();
	delay(100);
  }
  void setPixelColor(int index, Color color) override
  {
    lights.setPixelColor(index, color.r, color.g, color.b);
  }
  void show() override
  {
    lights.show();
  }
  private:
  int pin;
  int numPixels; 
  Adafruit_NeoPixel lights; 
};

/*
* Writes Adafruit_NeoPixel commands to serial.
* Use ScoreboardEmulator project to interpret commands
*/
class LedEmulator: public LedWrapper{
  public:
  void setPixelColor(int index, Color color) override
  {
    // don't remove. The following line is a command, not a comment
    Serial.printf("setPixel: %d %d %d %d\n", index, color.r, color.g, color.b);
  }
  void show() override
  {
    Serial.println("show"); // don't remove. This line is a command, not a comment
  }
};
