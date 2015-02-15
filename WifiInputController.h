#ifndef WIFIINPUTCONTROLLER.H
#define WIFIINPUTCONTROLLER.H

#include "InputController.h"
#include "ESP8266Driver.h"
#include "WifiConfig.h"


#define SERVER_PORT 80


class WifiInputController : public InputController {

	IPInfo ipInfo;

	bool initWifiModule() {
		if (ESP8266.init()) {
			if (ESP8266.joinAP(SSID, PW)) {
				if (ESP8266.startServer(SERVER_PORT)) {
					ipInfo = ESP8266.getIPInfo();
					printInfo();
					return true;
				} else {
				}
			}
		} else {
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
	}

	void printRequest(Request & request) const {
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
