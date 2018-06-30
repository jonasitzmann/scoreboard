#pragma once
#include "ScoreboardData.h"
class IConfigLoader {
 public:
  virtual ScoreboardData loadConfig() = 0;
};
class WhiteZeroLoader : public IConfigLoader {
 public:
  virtual ScoreboardData loadConfig() {
    ScoreboardData config = *new ScoreboardData();
    config.score1 = 0;
    config.score2 = 0;
    config.colorList1 = {std::make_shared<Color>(Color::WHITE)};
    config.colorList2 = {std::make_shared<Color>(Color::WHITE)};
    config.colorIndex1 = 0;
    config.colorIndex2 = 0;
    return config;
  }
};
