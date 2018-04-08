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
class ServerInOut :
	public InputDevice,
	public OutputDevice
{
	ESP8266WiFiMulti wifi;
	HTTPClient https;
	String fingerprint;
	String updateScoreUrl;
	String updateSettingsUrl;
	String sendRequest(String method, String url, String payload = "");
public:
	ServerInOut();
	virtual ~ServerInOut();

	// OutputDevice Interface
	virtual bool update(ScoreboardData newData);
	bool updateSettings(Color color1, Color color2, bool swappedSides);
	bool updateScores(int score1, int score2);

	// InputDevice Interface
	virtual InputDevice::Input getInput();
	virtual ScoreboardData init();
};

