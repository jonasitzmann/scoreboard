#include "StateMachine.h"

bool ConnectState::connectToWiFi()
{
	Serial.println("Connect to WiFi");
	int t0 = millis();
	WiFi.begin(cfg->ssid.c_str(), cfg->password.c_str());
	while (WiFi.status() != WL_CONNECTED) {
		if (millis() - t0 > 10000) {
			Serial.println();
			return false;
		}
		Serial.print(".");
		delay(300);
	}
	Serial.println();
	return true;
}

bool ConnectState::openWebSocket()
{
	Serial.println("Connect to Server");
	if (wfClient.get()->connect(cfg->hostIp, cfg->hostPort)) {
		Serial.println("Connection established.");
		return true;
	}
	else {
		Serial.println("Connection failed.");
		return false;
	}
}

bool ConnectState::handshake()
{
	wsClient.get()->path = "/";
	wsClient.get()->host = cfg->hostIp.c_str();
	if (wsClient.get()->handshake(*wfClient.get())) {
		Serial.println("Handshake successful");
		return true;
	}
	else {
		Serial.println("Handshake failed.");
		return false;
	}
}



std::shared_ptr<State> ConnectState::handle()
{
	if (!connectToWiFi()) {
		return std::make_shared<SleepState>(cfg);
	}
	if (!openWebSocket()) {
		return std::make_shared<SleepState>(cfg);
	}
	if (!handshake()) {
		return std::make_shared<SleepState>(cfg);
	}
	return std::make_shared<ShowScoreState>(cfg, wfClient, wsClient);
}