#pragma once
#include <string>
class ILogger {
public:
  enum Level { INFO, DEBUG, WARING, ERROR };
  virtual void log(std::string msg, Level level = INFO) = 0;
  virtual std::string echo(std::string msg) { return "not implemented"; }
};
