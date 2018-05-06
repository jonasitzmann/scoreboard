#pragma once
#include "ILogger.h"
#include <map>
#include <string.h>
#include <memory>
class SerialLogger :
	public ILogger

{
	SerialLogger();
	std::map<Level, std::string> levelNames =
	{
	{INFO, "INFO"},
	{DEBUG, "DEBUG"},
	{WARING, "WARNING"},
	{ERROR, "ERROR"}
	};
public:
	// Geerbt über ILogger
	virtual void log(std::string msg, Level level = INFO) override;
	static ILogger& GetInstance();
};

