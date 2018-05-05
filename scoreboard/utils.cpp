#include "utils.h"



std::string int2Str(int i)
{
	std::string str;
#ifdef UNIT_TEST
	std::stringstream stream;
	stream << i;
	str.append(stream.str());
#else
	String arduinoStr(i);
	std::string iStr(arduinoStr.c_str());
	str.append(iStr);
#endif
	return str;
}
