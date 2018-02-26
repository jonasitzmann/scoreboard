#pragma once
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WiFiMulti.h> 
#include <ESP8266mDNS.h>
#include <ESP8266WebServer.h>
String htmlForm =
"<form action=\"/results\" method=\"POST\">"
"<input type=\"text\" name=\"ssid\" placeholder=\"ssid\"></br>"
"<input type=\"text\" name=\"pwd\" placeholder=\"pwd\"></br>"
"<input type=\"text\" name=\"ip\" placeholder=\"ip\"></br>"
"<input type=\"text\" name=\"port\" placeholder=\"port\"></br>"
"<input type=\"text\" name=\"id\" placeholder=\"id\"></br>"
"<input type=\"text\" name=\"numPixels\" placeholder=\"numPixels\"></br>"
"<input type=\"text\" name=\"emulate\" placeholder=\"emulate\"></br>"
"Write: <input type = \"radio\" name = \"write\">"
"</br><input type=\"submit\" value=\"Save\"></form>";
class ConfigServer {
public:
	bool configChanged;
	ScoreboardConfiguration config;
	const char* ssid = "scoreboard";
	const char* password = "scoreboard";
	ESP8266WiFiMulti wifiMulti;
	ESP8266WebServer server;
public:
	ConfigServer() : server(80) {} // serve at port 80
	void handleRoot() {
		server.send(200, "text/html", htmlForm);
	}

	void handlePost() {
		// Post arguments are provided by server.arg("argName")
		if (server.hasArg("ssid") && server.arg("ssid") != "") {
			// copy arg to configuration
			strncpy(config.ssid, server.arg("ssid").c_str(), strlen(config.ssid));
			configChanged = true;
		}
		if (server.hasArg("pwd") && server.arg("pwd") != "") {
			strncpy(config.ssid, server.arg("ssid").c_str(), strlen(config.ssid));
			configChanged = true;
		}
		if (server.hasArg("ip") && server.arg("ip") != "") {
			strncpy(config.hostIp, server.arg("ip").c_str(), strlen(config.hostIp));
			configChanged = true;
		}
		if (server.hasArg("port") && server.arg("port") != "") {
			config.hostPort = server.arg("port").toInt();
			configChanged = true;
		}
		if (server.hasArg("id") && server.arg("id") != "") {
			strncpy(config.id, server.arg("id").c_str(), strlen(config.id));
			configChanged = true;
		}
		if (server.hasArg("numPixels") && server.arg("numPixels") != "") {
			config.numPixels = server.arg("numPixels").toInt();
			configChanged = true;
		}
		if (server.hasArg("emulate") && server.arg("emulate") != "") {
			config.useEmulator = server.arg("emulate").toInt();
			configChanged = true;
		}
		if (server.hasArg("write")) {
			if (server.arg("write") == "on") {
				config.save(); //write config to EEPROM
			}
		}
		server.send(200, "text/html", "<h1>Hello World");
		Serial.println(config.ssid);
		Serial.println(config.password);
		Serial.println(config.hostIp);
		Serial.println(config.hostPort);
		Serial.println(config.id);
		Serial.println(config.numPixels);
		Serial.println(config.useEmulator);
	}

	void handleNotFound() {
		server.send(404, "text/plain", "404: Not found");
	}
	void start() {
		WiFi.mode(WIFI_AP); //Only Access point
		WiFi.softAP(ssid, password);  //Start Hotspot

		server.on("/", HTTP_GET, std::bind(&ConfigServer::handleRoot, this));
		server.on("/results", HTTP_POST, std::bind(&ConfigServer::handlePost, this));
		server.onNotFound(std::bind(&ConfigServer::handleNotFound, this));

		server.begin();
		// Print Server IP to Serial
		Serial.print("HTTP server started at ");
		IPAddress myIP = WiFi.softAPIP();
		Serial.println(myIP);
	}
	ScoreboardConfiguration updateConfig(bool& changed) {
		server.handleClient();
		changed = configChanged;
		configChanged = false;
		Serial.println(config.hostPort);
		
		return config;
	}

};
