#ifndef WIFIINPUTCONTROLLER.H
#define WIFIINPUTCONTROLLER.H

#include "InputController.h"
#include "Logger.h"
#include "ESP8266Driver.h"


#define WIFI_SERIAL Serial


class WifiInputController : public InputController {

	ServerInfo serverInfo;

	void handleRequest() const {
		Request request;
		ESP8266.getRequest(request);
		printRequest(request);

		if (!strncmp(request.msg, "GET /", 5)) { // 0 = match
			char actionStr[] = {request.msg[5], '\0'};
			unsigned int action = atoi(actionStr);
			switch (action) {
				case 0:
					_stateMachine.turnOff();
					ESP8266.response(request.channel, "<a href='/1'>Turn ON</a>");
					break;
				case 1:
					_stateMachine.turnOn();
					ESP8266.response(request.channel, "<a href='/0'>Turn OFF</a>");
					break;
			}
		}
	}

	void printServerInfo() const {
		INFO_APPEND(serverInfo.ip);
		INFO_APPEND(':');
		INFO(serverInfo.port);
	}

	void printRequest(Request & request) const {
		INFO_APPEND("Wifi Channel: ");
		INFO_APPEND(request.channel);
		INFO_APPEND(" | ");
		INFO_APPEND("Length: ");
		INFO_APPEND(request.length);
		INFO_APPEND(" | ");
		INFO(request.msg);
	}

public:
	WifiInputController(StateMachine & stateMachine) : InputController(stateMachine) {}

	void init() {
		if (ESP8266.isServerRunning()) {
			ESP8266.getServerInfo(serverInfo);
			printServerInfo();
		}
	}

	void check() {
		if (ESP8266.isServerRunning() && ESP8266.hasNewConnection()) {
			handleRequest();
		}
	}
};

#endif
