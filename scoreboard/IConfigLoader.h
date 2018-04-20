#pragma once
#include "ScoreboardData.h"
class IConfigLoader
{
public:
	virtual ScoreboardData loadConfig() = 0;
};

