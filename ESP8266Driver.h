#ifndef ESP8266DRIVER.H
#define ESP8266DRIVER.H

#include "InputController.h"
#include "Logger.h"
#include "WifiConfig.h"


#define ESP8266 ESP8266Driver()

#define SERVER_PORT 80
#define WIFI_SERIAL Serial

#define REQUEST_MSG_BUFFER 100
#define LONG_TIMEOUT 5000
#define SHORT_TIMEOUT 10


bool WIFI_MODULE;
bool AP_CONNECTED;
bool SERVER_RUNNING;

struct ServerInfo {
	char ip[16];
	int port;
};

struct Request {
	int channel;
	size_t length;
	char msg[REQUEST_MSG_BUFFER];
};

class ESP8266Driver {

	template <typename T>
	bool send(T cmd, char* const ack='\0', bool const & append = false) const {
		LOG(cmd, append);

		// clear receive buffer
		while (WIFI_SERIAL.available()) WIFI_SERIAL.read();

		if (append) WIFI_SERIAL.print(cmd); else WIFI_SERIAL.println(cmd);
		delay(500);

		#ifdef DEBUG
			while (Serial.available() > 0) {
				char c = Serial.read();
				LOG_APPEND(c);
				LOG(c, HEX);
			}
		#endif

		return !ack || WIFI_SERIAL.find(ack);
		// if (ack) {
		// 	for (int i; i < 50; ++i) {
		// 		if (WIFI_SERIAL.findUntil(ack, "busy")) {
		// 			return true;
		// 		}
		// 		delay(1000);
		// 	}
		// 	return false;
		// }
		// return true;
	}

	template <typename T>
	bool append(T cmd) const {
		send(cmd, '\0', true);
	}

	// void send(const __FlashStringHelper* cmd) const {
	// 	send((char* const) cmd);
	// }

	bool reset() const {
		return send("AT+RST", "ready");
	}

	void initModule() const {
		send("AT+CWMODE=1");
		reset();
		send("AT+CIPSTO=0");
		send("AT+CIPMUX=1");
	}

	bool joinAP() const {
		append("AT+CWJAP=\"");
		append(SSID);
		append("\",\"");
		append(PW);
		send("\"", "OK");

		for (int i; i < 5; ++i) {
			INFO("Try Connecting to AP..");
			delay(2000);
			if (send("AT+CWJAP?", "+CWJAP:")) {
				// int ssidLength = strlen(SSID);
				// char connectedAP[ssidLength];
				// WIFI_SERIAL.readBytesUntil('\"', connectedAP, ssidLength);
				// connectedAP[ssidLength] = 0; // terminate string
				// INFO(connectedAP);
				// return !strncmp(connectedAP, SSID, ssidLength);
				AP_CONNECTED = true;
				return true;
			}
		}
		return false;
	}

	bool startServer() const {
		return send("AT+CIPSERVER=1,80", "OK");
	}

public:
	void init() const {
		delay(4000); // wait for module

		WIFI_SERIAL.begin(9600);
		WIFI_SERIAL.setTimeout(LONG_TIMEOUT);

		if (reset()) {
			INFO("Wifi Module detected!");
			WIFI_MODULE = true;
			INFO("Setup Wifi Module..");
			initModule();
			if (joinAP()) {
				INFO("Connected to AP!");
				if (startServer()) {
					INFO("Server started!");
					SERVER_RUNNING = true;
				} else {
					INFO("Server not running!");
				}
			}
		} else {
			INFO("Wifi Module is not available!");
		}

		WIFI_SERIAL.setTimeout(SHORT_TIMEOUT);
	}

	bool hasWifiModule() {
		return WIFI_MODULE;
	}

	bool isConnectedToAP() {
		return AP_CONNECTED;
	}

	bool isServerRunning() {
		return SERVER_RUNNING;
	}

	void getServerInfo(ServerInfo & serverInfo) const {
		WIFI_SERIAL.setTimeout(LONG_TIMEOUT);
		send("AT+CIFSR", "+CIFSR:STAIP,\"");
		WIFI_SERIAL.setTimeout(SHORT_TIMEOUT);

		size_t len = WIFI_SERIAL.readBytesUntil('\"', serverInfo.ip, 16);
		serverInfo.ip[len] = 0; // terminate string

		serverInfo.port = SERVER_PORT;
	}

	bool hasNewConnection() const {
		if (WIFI_SERIAL.findUntil("+IPD,", "\r")) {
			return true;
		}
		return false;
	}

	void getRequest(Request & request) const {
		request.channel = WIFI_SERIAL.parseInt();

		WIFI_SERIAL.find(":");

		request.length = WIFI_SERIAL.readBytesUntil('\r', request.msg, REQUEST_MSG_BUFFER);
		request.msg[request.length] = 0; // terminate string
	}

	void response(unsigned int const channel, char* const msg) const {
		INFO("response");
		append("AT+CIPSEND=");
		append(channel);
		append(",");
		send(strlen(msg), ">");
		WIFI_SERIAL.setTimeout(LONG_TIMEOUT);
		send(msg, "SEND OK");
		WIFI_SERIAL.setTimeout(SHORT_TIMEOUT);
		append("AT+CIPCLOSE=");
		send(channel);
	}
};

#endif
