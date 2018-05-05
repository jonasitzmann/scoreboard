#pragma once
#include "IHttpClient.h"
#include "ESP8266HTTPClient.h"
#include "ILogger.h"
class HttpWrapper :
	public IHttpClient
{
	std::string fingerprint;
	std::shared_ptr<HTTPClient> https;
	std::shared_ptr<ILogger> logger;
public:
	HttpWrapper(std::shared_ptr<ILogger> logger);
	~HttpWrapper();

	// Geerbt über IHttpClient
	virtual bool begin() override;
	virtual std::string sendRequest(std::string method, std::string url, std::string payload = "") override;
	virtual std::string getString() override;
	virtual std::string errorToString(int code) override;
};

