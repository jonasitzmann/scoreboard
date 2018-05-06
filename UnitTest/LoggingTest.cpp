#pragma once
#include "stdafx.h"
#include <CppUnitTest.h>
#include "LoggerFactory.h"
#include "LoggerFactory.cpp"
#include <string>
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest
{
	TEST_CLASS(LoggingTest)
	{
	public:
		TEST_METHOD(CoutLogger_ctor)
		{
			ILogger &logger = LoggerFactory::getLogger();
		}
		TEST_METHOD(Logger_OnlyOneInstance)
		{
			ILogger &logger1 = LoggerFactory::getLogger();
			ILogger &logger2 = LoggerFactory::getLogger();
			Assert::IsTrue(&logger1 == &logger2);
		}
	};
}