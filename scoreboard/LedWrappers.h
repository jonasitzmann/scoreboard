#include "Color.h"
#include "LoggerFactory.h"
#include <Adafruit_NeoPixel.h>
#include <memory>
#include <stdlib.h>
#include <string>
class LedWrapper {
protected:
  ILogger &logger;

public:
  LedWrapper() : logger(LoggerFactory::getLogger()) {}
  virtual void setPixelColor(int index, Color color) = 0;
  virtual void show() = 0;
};

/*
 * Wrapper for the Adafruit_NeoPixel library.
 * Forwards commands to Adafruit_NeoPixel instance
 */
class NeoPixelWrapper : public LedWrapper {
public:
  NeoPixelWrapper(int pin = D5, int numPixels = 142)
      : pin(pin), numPixels(numPixels) {
    lights = *new Adafruit_NeoPixel(
        numPixels, pin,
        /*suitable pixel flags for our LED Strip*/ NEO_GRB + NEO_KHZ800);
    lights.begin();
    delay(100);
  }
  void setPixelColor(int index, Color color) override {
    lights.setPixelColor(index, color.r, color.g, color.b);
  }
  void show() override { lights.show(); }

private:
  int pin;
  int numPixels;
  Adafruit_NeoPixel lights;
};

/*
 * Writes Adafruit_NeoPixel commands to serial.
 * Use ScoreboardEmulator project to interpret commands
 */
class LedEmulator : public LedWrapper {
public:
  void setPixelColor(int index, Color color) override {
    // don't remove. The following line is a command, not a comment
    char indexS[10];
    char rS[10];
    char gS[10];
    char bS[10];
    itoa(index, indexS, 10);
    itoa(color.r, rS, 10);
    itoa(color.g, gS, 10);
    itoa(color.b, bS, 10);
    logger.log("setPixel: " + std::string(indexS) + " " + std::string(rS) +
               " " + std::string(gS) + " " + std::string(bS));
  }
  void show() override {
    logger.log("show"); // don't remove. This line is a command, not a comment
  }
};
