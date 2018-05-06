#pragma once
#include "ILogger.h"
#include <string>
#include <iostream>
#include <memory>
#include <CppUnitTest.h>
class CoutLogger :
	public ILogger
{
	CoutLogger()
	{
	}
public:
	// Geerbt über ILogger
	void log(std::string msg, Level level) override
	{
		using namespace Microsoft::VisualStudio::CppUnitTestFramework;
		Logger::WriteMessage(msg.c_str());
	}
	std::string echo(std::string msg)override {
		return msg;
	}

	static ILogger& GetInstance()
	{
		static CoutLogger instance;
		return instance;
	}

};

