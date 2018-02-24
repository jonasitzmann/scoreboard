#include <EEPROM.h>
static const int CONFIG_BEGIN = 0;
struct Configuration{
  char SSID[30];
  char password[30];
  char hostIp[30];
  int hostPort;
  bool useEmulator;
  int numPixels;
  static Configuration load(){
    Configuration cfg;
    EEPROM.begin(4095);
    EEPROM.get( CONFIG_BEGIN, cfg );
    EEPROM.end();
  }
  void save(){
    EEPROM.begin(4095);
    EEPROM.put(CONFIG_BEGIN, *this );
    delay(200);
    EEPROM.commit();
    EEPROM.end();
  }
};



