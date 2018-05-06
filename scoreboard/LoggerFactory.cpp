#include "LoggerFactory.h"
ILogger& LoggerFactory::getLogger()
{
#ifdef UNIT_TEST
	return CoutLogger::GetInstance();
#else
	return SerialLogger::GetInstance();
#endif
}
