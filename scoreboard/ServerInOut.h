#pragma once
#include "OutputDevice.h"
#include "InputDevice.h"
#include "ScoreboardData.h"
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>

#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>
#include <JsonStreamingParser.h>
#define S(x) #x
#define STR(x) S(x)
extern String ssid1;
extern String ssid2;
extern String pwd1;
extern String pwd2;
class ServerOutput :
	public InputDevice,
	public OutputDevice
{
	ESP8266WiFiMulti wifi;
	HTTPClient https;
	String fingerprint;
	String updateUrl;
	String sendRequest(String method, String url, String payload = "");
public:
	ServerOutput();
	virtual ~ServerOutput();

	// OutputDevice Interface
	virtual void update();
	virtual bool updateRScore(int newScore);
	virtual bool updateLScore(int newScore);
	virtual bool updateRColor(Color newColor);
	virtual bool updateLColor(Color newColor);
	virtual bool updateAll(
		int rScore_,
		int lScore_,
		Color rColor_,
		Color lColor_
	);

	// InputDevice Interface
	virtual InputDevice::Input getInput();
	virtual ScoreboardData init();
};

