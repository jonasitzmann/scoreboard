#pragma once
#include <ESP8266WiFi.h>
#include <WebSocketClient.h>
class WebSocketHandler {
	const char* ssid;
	const char* password;
	char m_hostIp[30];
	int hostPort;
	WebSocketClient webSocketClient;

	WiFiClient client;
public:
	WebSocketHandler(const char* ssid = "", const char* password = "", const char* hostIp = "", int hostPort = -1) :
		ssid(ssid), password(password), hostPort(hostPort) {
		strncpy(m_hostIp, hostIp, 30);
	}	
	bool connectToServer() {
		Serial.println("connecting to WiFi");
		Serial.print("SSID: ");
		Serial.println(ssid);
		Serial.print("Password: ");
		Serial.println(password);
		if (!connectToWifi()) {
			return false;
		}
		Serial.println("Opening WebSocket");
		Serial.print("Host Ip: ");
		Serial.println(m_hostIp);
		Serial.print("Port: ");
		Serial.println(hostPort);
		if (!openWebSocket()) {
			return false;
		}
		if (!handshake()) {
			return false;
		}
		return true;
	}

	bool connectToWifi() {
		int t0 = millis();
		WiFi.begin("EasyBox-522111", "DdPA7As6kYKLDMKV");
		while (WiFi.status() != WL_CONNECTED) {
			if (millis() - t0 > 10000) {
				return false;
			}
			delay(200);
		}
		return true;
	}

	bool openWebSocket() {
		if (client.connect(m_hostIp, hostPort)) {
			Serial.println("Connection established.");
			return true;
		}
		else {
			Serial.println("Connection failed.");
			return false;
		}
	}

	bool handshake() {
		webSocketClient.path = "/";
		Serial.print("Host IP: ");
		Serial.println(m_hostIp);
		webSocketClient.host = m_hostIp;
		if (webSocketClient.handshake(client)) {
			Serial.println("Handshake successful");
			return true;
		}
		else {
			Serial.println("Handshake failed.");
			return false;
		}
	}
	bool isConnected() {
		return client.connected();
	}
	String getData() {
		String data;
		webSocketClient.getData(data);
		return data;
	}
};

