#pragma once
#include <string>
class IHttpClient
{
public:
	virtual bool begin() = 0;
	virtual std::string sendRequest(std::string method, std::string url, std::string payload = "") = 0;
	virtual std::string getString() = 0;
	virtual std::string errorToString(int code) = 0;
	virtual ~IHttpClient() {}
};

