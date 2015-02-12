#ifndef WIFIINPUTCONTROLLER.H
#define WIFIINPUTCONTROLLER.H

#include "InputController.h"
#include "Logger.h"
#include "WifiConfig.h"


#define WIFI_SERIAL Serial


class WifiInputController : public InputController {

	template <typename T>
	bool send(T cmd, char* const ack='\0', bool const & append = false) {
		LOG(cmd, append);
		if (append) WIFI_SERIAL.print(cmd); else WIFI_SERIAL.println(cmd);

		#ifdef DEBUG
		while (Serial.available() > 0) {
			char c = Serial.read();
			LOG_APPEND(c);
			LOG(c, HEX);
		}
		#endif

		return !ack || WIFI_SERIAL.find(ack);
	}

	template <typename T>
	bool append(T cmd) {
		send(cmd, '\0', true);
	}

	void send(const __FlashStringHelper* cmd) {
		send((char* const) cmd);
	}

	bool reset() {
		return send("AT+RST", "ready");
	}

	void initModule() {
		send("AT+CWMODE=1");
		reset();
		send("AT+CIPMUX=1");
		send("AT+CIPSTO=0");
	}

	bool joinAP() {
		append("AT+CWJAP=\"");
		append(SSID);
		append("\",\"");
		append(PW);
		send("\"", "OK");

		for (int i; i < 5; ++i) {
			INFO("Try connecting..");
			if (send("AT+CWJAP?", "+CWJAP:")) {
				return true;
			}
		}
		return false;
	}

	bool startServer() {
		return send("AT+CIPSERVER=1,80", "OK");
	}

	void response(unsigned int const channel, char* const msg, unsigned int msgLength) {
		append("AT+CIPSEND=");
		append(channel);
		append(",");
		send(msgLength, ">");
		send(msg, "SEND OK");
		append("AT+CIPCLOSE=");
		send(channel);
	}

	void handleConnection() {
		unsigned int channel = WIFI_SERIAL.parseInt();
		INFO_APPEND("Wifi Channel: ");
		INFO_APPEND(channel);
		INFO_APPEND(" | ");

		if (WIFI_SERIAL.findUntil("GET /", "\r")) {
			unsigned int action = WIFI_SERIAL.parseInt();
			switch (action) {
				case 0:
					INFO("GET /0");
					_stateMachine.turnOff();
					response(channel, "<a href='/1'>Turn ON</a>", 23);
					break;
				case 1:
					INFO("GET /1");
					_stateMachine.turnOn();
					response(channel, "<a href='/0'>Turn OFF</a>", 24);
					break;
			}
		}
	}


public:
	WifiInputController(StateMachine & stateMachine) : InputController(stateMachine) {}

	void init() {
		delay(3000); // wait for module

		WIFI_SERIAL.begin(9600);
		WIFI_SERIAL.setTimeout(5000);

		if (reset()) {
			INFO("Wifi Module detected!");
			initModule();
			if(joinAP()) {
				INFO("Connected to AP");
				send("AT+CIFSR", "+CIFSR");
				if(startServer()) {
					INFO("Server started!");
				}
			}
		} else {
			INFO("Wifi Module is not available!");
		}

		// WIFI_SERIAL.setTimeout(100);
	}

	void check() {
		while (WIFI_SERIAL.available() > 0) {
			if (WIFI_SERIAL.findUntil("+IPD,", "\r")) {
				handleConnection();
			}
		}
	}
};

#endif
