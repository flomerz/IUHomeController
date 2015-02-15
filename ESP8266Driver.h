#ifndef ESP8266DRIVER.H
#define ESP8266DRIVER.H

#include "InputController.h"


#define ESP8266 ESP8266Driver()

#define WIFI_SERIAL Serial

#define WIFI_SERIAL_BAUD 9600

#define TIMEOUT_LONG 10000
#define TIMEOUT_DEFAULT 5000
#define TIMEOUT_SEND 200
#define TIMEOUT_SHORT 20

#define AP_CONNECT_TRIES 5
#define CHECK_AP_CONNECTED_INTERVAL 180000

#define REQUEST_MSG_BUFFER_SIZE 100


unsigned long CURRENT_TIMEOUT = TIMEOUT_DEFAULT;

bool AP_CONNECTED;
long LAST_AP_CONNECTED_CHECK_MILLIS = -CHECK_AP_CONNECTED_INTERVAL;

struct IPInfo {
	char ip[16];
};

struct Request {
	int channel;
	size_t length;
	char msg[REQUEST_MSG_BUFFER_SIZE];
};

class ESP8266Driver {

	template <typename T>
	bool send(T cmd, char* const ack = "OK", unsigned long const & timeout = TIMEOUT_DEFAULT) const {
		while (WIFI_SERIAL.available()) WIFI_SERIAL.read(); // clear receive buffer


		if (CURRENT_TIMEOUT != timeout) {
			CURRENT_TIMEOUT = timeout;
			WIFI_SERIAL.setTimeout(timeout);
		}

		WIFI_SERIAL.println(cmd);
		delay(10);
		return !ack || WIFI_SERIAL.find(ack);
	}

	bool reset() const {
		return send("AT+RST", "ready");
	}

public:
	bool init() const {
		WIFI_SERIAL.begin(WIFI_SERIAL_BAUD);
		WIFI_SERIAL.setTimeout(TIMEOUT_DEFAULT);

		if (reset()) {
			if (send("AT+CWMODE=1")) {
				if (reset()) {
					return send("AT+CIPMUX=1");
				}
			}
		}
		return false;
	}

	bool joinAP(char* const ssid, char* const password) const {
		char cmd[128];
		sprintf(cmd, "AT+CWJAP=\"%s\",\"%s\"", ssid, password);

		for (int i = 0; i < AP_CONNECT_TRIES; ++i) {
			if (send(cmd, "OK", TIMEOUT_LONG)) {
				LAST_AP_CONNECTED_CHECK_MILLIS = -CHECK_AP_CONNECTED_INTERVAL; // ignore check interval
				return isConnectedToAP(ssid, 0);
			}
		}
		return false;
	}

	bool isConnectedToAP(char* const ssid, unsigned long currentMillis) const {
		if (currentMillis - LAST_AP_CONNECTED_CHECK_MILLIS >= CHECK_AP_CONNECTED_INTERVAL || currentMillis < LAST_AP_CONNECTED_CHECK_MILLIS) {
			LAST_AP_CONNECTED_CHECK_MILLIS = currentMillis;

			char cmd[62];
			sprintf(cmd, "+CWJAP:\"%s\"", ssid);

			AP_CONNECTED = send("AT+CWJAP?", cmd);
		}
		return AP_CONNECTED;
	}

	bool startServer(unsigned int port) const {
		char cmd[24];
		sprintf(cmd, "AT+CIPSERVER=1,%i", port);

		if (send(cmd)) {
			if(send("AT+CIPSTO=1")) {
				WIFI_SERIAL.setTimeout(TIMEOUT_SHORT);
				return true;
			}
		}
		return false;
	}

	IPInfo getIPInfo() const {
		IPInfo ipInfo;

		send("AT+CIFSR", "+CIFSR:STAIP,\"");

		size_t len = WIFI_SERIAL.readBytesUntil('\"', ipInfo.ip, 16);
		ipInfo.ip[len] = 0; // terminate string

		return ipInfo;
	}

	bool hasNewConnection() const {
		if (WIFI_SERIAL.findUntil("+IPD,", "\r")) {
			return true;
		}
		return false;
	}

	Request getRequest() const {
		Request request;
		request.channel = WIFI_SERIAL.parseInt();

		WIFI_SERIAL.find(":");

		request.length = WIFI_SERIAL.readBytesUntil('\r', request.msg, REQUEST_MSG_BUFFER_SIZE);
		request.msg[request.length] = 0; // terminate string

		return request;
	}

	void response(unsigned int const & channel, char* const msg) const {
		char cmd[24];
		sprintf(cmd, "AT+CIPSEND=%i,%i", channel, strlen(msg));
		send(cmd, ">", TIMEOUT_SHORT);

		send(msg, "SEND OK", TIMEOUT_SEND);
	}

	void close(unsigned int const & channel) const {
		char cmd[16];
		sprintf(cmd, "AT+CIPCLOSE=%i", channel);
		send(cmd, false, TIMEOUT_SHORT);
	}
};

#endif
