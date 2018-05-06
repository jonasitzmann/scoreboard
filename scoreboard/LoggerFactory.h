#pragma once
#include <memory>
#ifdef UNIT_TEST
#include "CoutLogger.h"
#else
#include "SerialLogger.h"
#endif
class LoggerFactory
{
public:
	static ILogger& getLogger();
};

