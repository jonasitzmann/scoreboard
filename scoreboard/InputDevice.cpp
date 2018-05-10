#include "InputDevice.h"
#include <map>

SerialInput::SerialInput() { Serial.setTimeout(10); }

std::vector<InputDevice::Input> SerialInput::getInput() {
  using namespace std;
  vector<InputDevice::Input> inputs;
  String serialStr = Serial.readString();
  if (serialStr.length() == 0) {
    return inputs;
  }
  std::map<String, InputDevice::Input> string2Input = {
      {"lPlus", L_PLUS},   {"lMinus", L_MINUS}, {"rPlus", R_PLUS},
      {"rMinus", R_MINUS}, {"rColor", R_COLOR}, {"lColor", L_COLOR},
      {"swap", SWAP},      {"reset", RESET},    {"lock", LOCK},
      {"unlock", UNLOCK}};
  for (auto itr = begin(string2Input); itr != end(string2Input); ++itr) {
    if (serialStr == itr->first) {
      inputs.push_back(itr->second);
    }
  }
  return inputs;
}

ButtonInput::ButtonInput() {
  pcf8574.begin(0x20, D1, D2);
  for (auto itr = begin(inputMap); itr != end(inputMap); ++itr) {
    previousPressed[itr->first] = false;
  }
}

std::vector<InputDevice::Input> ButtonInput::getInput() {
  vector<Input> inputs;
  uint8_t input = ~pcf8574.getByte();
  for (auto itr = begin(inputMap); itr != end(inputMap); ++itr) {
    uint8_t filter = 0x01 << itr->first;
    bool isPressed = (input & filter) != 0;
    if (isPressed && !previousPressed[itr->first]) {
      inputs.push_back(itr->second);
    }
    previousPressed[itr->first] = isPressed;
  }
  return inputs;
}

int CmpPins::gpio2Pin(const int &val) {
  switch (val) {
  case D0:
    return 0;
  case D1:
    return 1;
  case D2:
    return 2;
  case D3:
    return 3;
  case D4:
    return 4;
  case D5:
    return 5;
  case D6:
    return 6;
  case D7:
    return 7;
  case D8:
    return 8;
  case D9:
    return 9;
  case D10:
    return 10;

  default:
    return -1;
  }
}
