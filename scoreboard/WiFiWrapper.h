#pragma once
#include "IWiFi.h"
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include "LoggerFactory.h"

#define S(x) #x
#define STR(x) S(x)
extern String ssid1;
extern String ssid2;
extern String pwd1;
extern String pwd2;

class WiFiWrapper :
	public IWiFi
{
	ESP8266WiFiMulti wifi;
	ILogger& logger;

public:
	WiFiWrapper();
	~WiFiWrapper() override {};

	// Geerbt �ber IWiFi
	virtual bool begin() override;
};

