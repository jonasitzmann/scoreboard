#pragma once
class IWiFi
{
public:
	virtual bool begin() = 0;
	virtual ~IWiFi() {};
};

