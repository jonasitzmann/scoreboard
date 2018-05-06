#include "SerialLogger.h"
#include "Arduino.h"

SerialLogger::SerialLogger()
{
	Serial.begin(115200);
	delay(100);
	Serial.println();
}

void SerialLogger::log(std::string msg, Level level)
{
	std::string formated = "[" + levelNames[level] + "]: ";
	formated += msg;
	Serial.println(msg.c_str());
}

ILogger& SerialLogger::GetInstance()
{
	static SerialLogger instance;
	return instance;
}
