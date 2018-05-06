#include "stdafx.h"
#include "CppUnitTest.h"
#include "Color.h"
#include "Color.cpp"
#include "utils.cpp"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest
{		
	TEST_CLASS(ColorTest)
	{
	public:
		TEST_METHOD(default_ctor_white)
		{
			Color defaultColor;
			Assert::AreEqual(255, defaultColor.r);
			Assert::AreEqual(255, defaultColor.g);
			Assert::AreEqual(255, defaultColor.b);
			Assert::AreEqual(static_cast<int>(Color::WHITE), static_cast<int>(defaultColor.type));
			Assert::AreEqual(std::string("color: {	type: 0	r:255	g:255	b:255}"), defaultColor.toString());
		}
		TEST_METHOD(colortype_ctor)
		{
			Color red(Color::RED);
			Assert::AreEqual(255, red.r);
			Assert::AreEqual(0, red.g);
			Assert::AreEqual(0, red.b);
			Assert::AreEqual(static_cast<int>(Color::RED), static_cast<int>(red.type));
			
			Color green(Color::GREEN);
			Assert::AreEqual(0, green.r);
			Assert::AreEqual(255, green.g);
			Assert::AreEqual(0, green.b);
			Assert::AreEqual(static_cast<int>(Color::GREEN), static_cast<int>(green.type));
			
			Color blue(Color::BLUE);
			Assert::AreEqual(0, blue.r);
			Assert::AreEqual(0, blue.g);
			Assert::AreEqual(255, blue.b);
			Assert::AreEqual(static_cast<int>(Color::BLUE), static_cast<int>(blue.type));
			
			Color white(Color::WHITE);
			Assert::AreEqual(255, white.r);
			Assert::AreEqual(255, white.g);
			Assert::AreEqual(255, white.b);
			Assert::AreEqual(static_cast<int>(Color::WHITE), static_cast<int>(white.type));
		}
	};
}