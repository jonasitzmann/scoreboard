#pragma once
#include <EEPROM.h>
#include <string.h>
/*
ssid = "EasyBox-522111"
hostIp = "192.168.2.112"
password = ""
hostPort = 8000
numPixels = 70
useEmulator = true
id = "Scoreboard1"
;*/
	static const int CONFIG_BEGIN = 0;
	class Configuration {
		typedef struct {
			char id[30];
			char ssid[30];
			char password[30];
			char hostIp[30];
			int hostPort;
			bool useEmulator;
			int numPixels;
		} config_t;
	public:
		Configuration() {}
		String id;
		String ssid;
		String password;
		String hostIp;
		int hostPort;
		bool useEmulator;
		int numPixels;
		void load() {
			EEPROM.begin(4095);
			EEPROM.get(CONFIG_BEGIN, m_config);
			delay(50);
			EEPROM.end();
			id = String(m_config.id);
			ssid = String(m_config.ssid);
			password = String(m_config.password);
			hostIp = String(m_config.hostIp);
			hostPort = m_config.hostPort;
			useEmulator = m_config.useEmulator;
			numPixels = m_config.numPixels;
		}
		void save() {
			id.toCharArray(m_config.id, 30);
			ssid.toCharArray(m_config.ssid, 30);
			password.toCharArray(m_config.password, 30);
			hostIp.toCharArray(m_config.hostIp, 30);
			m_config.useEmulator = useEmulator;
			m_config.numPixels = numPixels;
			m_config.hostPort = hostPort;


			EEPROM.begin(200);
			for(int i = 0; i < 200; ++i){
				EEPROM.write(i, 0);	
			}
			EEPROM.commit();
			EEPROM.end();
			EEPROM.begin(200);
			EEPROM.put(CONFIG_BEGIN, m_config);
			delay(100);
			EEPROM.commit();
			EEPROM.end();
		}
		String toString() {
			String str;
			str += "\n";
			str += "----------- Configuration: -----------------\n";
			str += "| id: " + String(id) + "\n";
			str += "| ssid: " + String(ssid) + "\n";
			str += "| password: " + String(password) + "\n";
			str += "| hostIp: " + String(hostIp) + "\n";
			str += "| hostPort: " + String(hostPort) + "\n";
			str += "| numPixels: " + String(numPixels) + "\n";
			str += "| useEmulator: " + String(useEmulator) + "\n";
			str += "--------------------------------------------\n";
			return str;
		}
		config_t m_config;
	};



