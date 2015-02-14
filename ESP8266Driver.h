#ifndef ESP8266DRIVER.H
#define ESP8266DRIVER.H

#include "InputController.h"
#include "Logger.h"


#define ESP8266 ESP8266Driver()

#define WIFI_SERIAL Serial

#define WIFI_SERIAL_BAUD 9600

#define LONG_TIMEOUT 30000
#define SHORT_TIMEOUT 5000

#define AP_CONNECT_TRIES 5
#define CHECK_AP_CONNECTED_INTERVAL 180000

#define SERVER_PORT 80

#define REQUEST_MSG_BUFFER_SIZE 100


bool AP_CONNECTED;
long LAST_AP_CONNECTED_CHECK_MILLIS = -CHECK_AP_CONNECTED_INTERVAL;

struct IPInfo {
	char ip[16];
	int port;
};

struct Request {
	int channel;
	size_t length;
	char msg[REQUEST_MSG_BUFFER_SIZE];
};

class ESP8266Driver {

	template <typename T>
	bool send(T cmd, char* const ack = "OK") const {
		while (WIFI_SERIAL.available()) WIFI_SERIAL.read(); // clear receive buffer

		DEBUG_APPEND(cmd);
		DEBUG_APPEND(" -> ");
		DEBUG(ack);

		WIFI_SERIAL.println(cmd);
		delay(20);
		return !ack || WIFI_SERIAL.find(ack);
	}

	bool reset() const {
		return send("AT+RST", "ready");
	}

public:
	bool init() const {
		WIFI_SERIAL.begin(WIFI_SERIAL_BAUD);
		WIFI_SERIAL.setTimeout(SHORT_TIMEOUT);

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
		char buf[128];
		sprintf(buf, "AT+CWJAP=\"%s\",\"%s\"", ssid, password);
		
		for (int i = 0; i < AP_CONNECT_TRIES; ++i) {
			INFO("Try Connecting to AP..");
			WIFI_SERIAL.setTimeout(LONG_TIMEOUT);
			bool cmdSent = send(buf);
			WIFI_SERIAL.setTimeout(SHORT_TIMEOUT);
			if (cmdSent) {
				LAST_AP_CONNECTED_CHECK_MILLIS = -CHECK_AP_CONNECTED_INTERVAL; // ignore check interval
				return isConnectedToAP(ssid, 0);
			}
		}
		return false;
	}

	bool isConnectedToAP(char* const ssid, unsigned long currentMillis) const {
		if (currentMillis - LAST_AP_CONNECTED_CHECK_MILLIS >= CHECK_AP_CONNECTED_INTERVAL || currentMillis < LAST_AP_CONNECTED_CHECK_MILLIS) {
			LAST_AP_CONNECTED_CHECK_MILLIS = currentMillis;

			char buf[62];
			sprintf(buf, "+CWJAP:\"%s\"", ssid);

			AP_CONNECTED = send("AT+CWJAP?", buf);
		}
		return AP_CONNECTED;
	}

	bool startServer() const {
		if (send("AT+CIPSERVER=1,80")) {
			return send("AT+CIPSTO=1");
		}
		return false;
	}

	IPInfo getIPInfo() const {
		IPInfo ipInfo;

		send("AT+CIFSR", "+CIFSR:STAIP,\"");

		size_t len = WIFI_SERIAL.readBytesUntil('\"', ipInfo.ip, 16);
		ipInfo.ip[len] = 0; // terminate string

		ipInfo.port = SERVER_PORT;

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
		char buf[24];
		sprintf(buf, "AT+CIPSEND=%i,%i", channel, strlen(msg));
		send(buf, ">");

		send(msg, false);
	}

	void close(unsigned int const & channel) const {
		char buf[16];
		sprintf(buf, "AT+CIPCLOSE=%i", channel);
		send(buf, false);
	}
};

#endif