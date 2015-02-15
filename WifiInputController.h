#ifndef WIFIINPUTCONTROLLER.H
#define WIFIINPUTCONTROLLER.H

#include "InputController.h"
#include "Logger.h"
#include "ESP8266Driver.h"
#include "WifiConfig.h"


#define SERVER_PORT 80


class WifiInputController : public InputController {

	IPInfo ipInfo;

	bool initWifiModule() {
		INFO("init Wifi Module..");
		if (ESP8266.init()) {
			INFO("Wifi Module initialized!");
			INFO("try connecting to AP..");
			if (ESP8266.joinAP(SSID, PW)) {
				INFO("connected to AP!");
				if (ESP8266.startServer(SERVER_PORT)) {
					INFO("Server started!");
					ipInfo = ESP8266.getIPInfo();
					printInfo();
					return true;
				} else {
					INFO("Server not running!");
				}
			} else {
				INFO("AP not in reach or wrong password!");
			}
		} else {
			INFO("Wifi Module is not available!");
		}
		return false;
	}

	void handleRequest() const {
		Request request = ESP8266.getRequest();
		printRequest(request);

		if (!strncmp(request.msg, "GET /", 5)) { // 0 = match
			char actionStr[] = {request.msg[5], '\0'};
			unsigned int action = atoi(actionStr);
			switch (action) {
				case 0:
					_stateMachine.blockMotion();
					_stateMachine.turnOff();
					ESP8266.response(request.channel, "<a href='/1'>Turn ON</a>");
					break;
				case 1:
					_stateMachine.blockMotion();
					_stateMachine.turnOn();
					ESP8266.response(request.channel, "<a href='/0'>Turn OFF</a>");
					break;
			}
		}
		ESP8266.close(request.channel);
	}

	void printInfo() const {
		INFO_APPEND(ipInfo.ip);
		INFO_APPEND(':');
		INFO(SERVER_PORT);
	}

	void printRequest(Request & request) const {
		INFO_APPEND("Wifi channel: ");
		INFO_APPEND(request.channel);
		INFO_APPEND(" | ");
		INFO_APPEND("length: ");
		INFO_APPEND(request.length);
		INFO_APPEND(" | ");
		INFO(request.msg);
	}

public:
	WifiInputController(StateMachine & stateMachine) : InputController(stateMachine) {}

	void init() {
		if (!initWifiModule()) {
			asm volatile (" jmp 0"); // reset arduino
		}
	}

	void check() {
		if (!ESP8266.isConnectedToAP(SSID, millis())) {
			initWifiModule();
		}
		if (ESP8266.hasNewConnection()) {
			handleRequest();
		}
	}
};

#endif
