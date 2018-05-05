#pragma once
#include "ILogger.h"
#include <map>
#include <string.h>
class SerialLogger :
	public ILogger

{
	std::map<Level, std::string> levelNames =
	{
	{INFO, "INFO"},
	{DEBUG, "DEBUG"},
	{WARING, "WARNING"},
	{ERROR, "ERROR"}
	};
public:
	SerialLogger();
	virtual ~SerialLogger();

	// Geerbt über ILogger
	virtual void log(std::string msg, Level level = INFO) override;
};

