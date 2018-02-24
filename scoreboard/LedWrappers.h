#include <Adafruit_NeoPixel.h>

class LedWrapper{
  public:
  virtual void setPixelColor(int index, int red, int green, int blue) = 0;
  virtual void show() = 0;
};

class NeoPixelWrapper: public LedWrapper{
  public:
  NeoPixelWrapper(int pin = D1, int numPixels = 70): pin(pin), numPixels(numPixels){
    lights = * new Adafruit_NeoPixel(numPixels, pin,
                 /*suitable pixel flags for our LED Strip*/NEO_GRB + NEO_KHZ800
               );
    lights.begin();
  }
  virtual void setPixelColor(int index, int red, int green, int blue){
    lights.setPixelColor(index, red, green, blue);
  }
  virtual void show(){
    lights.show();
  }
  private:
  int pin;
  int numPixels; 
  Adafruit_NeoPixel lights; 
};


class LedEmulator: public LedWrapper{
  public:
  LedEmulator(){
    Serial.begin(115200);
  }
  virtual void setPixelColor(int index, int red, int green, int blue){
    Serial.printf("setPixel: %d %d %d %d\n", index, red, green, blue);
  }
  virtual void show(){
    Serial.println("show");
  }
};
