#pragma once
#include <pcf8574_esp.h>
#include <map>
#include "Arduino.h"
#include "ScoreboardData.h"
class InputDevice {
 public:
  enum Input {
    NO_INPUT,
    L_COLOR,
    L_PLUS,
    L_MINUS,
    R_COLOR,
    R_PLUS,
    R_MINUS,
    LOCK,
    RESET,
    SWAP,
    UNLOCK
  };
  std::map<Input, std::string> input2Name = {
      {NO_INPUT, "NO_INPUT"}, {L_COLOR, "L_COLOR"}, {L_PLUS, "L_PLUS"},
      {L_MINUS, "L_MINUS"},   {R_COLOR, "R_COLOR"}, {R_PLUS, "R_PLUS"},
      {R_MINUS, "R_MINUS"},   {LOCK, "LOCK"},       {RESET, "RESET"},
      {SWAP, "SWAP"},         {UNLOCK, "UNLOCK"}};
  virtual std::vector<Input> getInput() = 0;
};

class SerialInput : public InputDevice {
 public:
  SerialInput();
  virtual std::vector<Input> getInput();
};

struct CmpPins {
  static int gpio2Pin(const int& val);
  bool operator()(const int& lhs, const int& rhs) {
    return gpio2Pin(lhs) < gpio2Pin(rhs);
  }
};

class ButtonInput : public InputDevice {
  PCF857x pcf8574;
  std::map<uint8_t, Input> inputMap = {{0, L_COLOR}, {1, L_MINUS}, {2, L_PLUS},
                                       {3, R_COLOR}, {4, R_MINUS}, {5, R_PLUS},
                                       {6, RESET},   {7, SWAP}};
  std::map<uint8_t, bool> previousPressed;

 public:
  ButtonInput();
  virtual std::vector<Input> getInput();
};
