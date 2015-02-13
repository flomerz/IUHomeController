#ifndef ESP8266DRIVER.H
#define ESP8266DRIVER.H

#include "InputController.h"
#include "Logger.h"
#include "WifiConfig.h"


#define ESP8266 ESP8266Driver()

#define WIFI_SERIAL Serial

#define AP_CONNECT_TRIES 5
#define SERVER_PORT 80

#define REQUEST_MSG_BUFFER 100
#define LONG_TIMEOUT 10000
#define SHORT_TIMEOUT 10

#define CHECK_AP_CONNECTED_INTERVAL 60000


bool WIFI_MODULE;
bool AP_CONNECTED;
bool SERVER_RUNNING;

long LAST_AP_CONNECTED_CHECK_MILLIS = -CHECK_AP_CONNECTED_INTERVAL;

unsigned long CURRENT_TIMEOUT = LONG_TIMEOUT;
unsigned long OLD_TIMEOUT = LONG_TIMEOUT;

struct IPInfo {
	char ip[16];
	int port;
};

struct Request {
	int channel;
	size_t length;
	char msg[REQUEST_MSG_BUFFER];
};

class ESP8266Driver {

	void setTimeout(unsigned long const & timeout) const {
		WIFI_SERIAL.setTimeout(timeout);
		OLD_TIMEOUT = CURRENT_TIMEOUT;
		CURRENT_TIMEOUT = timeout;
	}

	void resetTimeout() const {
		setTimeout(OLD_TIMEOUT);
	}

	template <typename T>
	bool send(T cmd, char* const ack = "OK") const {
		if (!SERVER_RUNNING) delay(200); // lazy setup

		// clear receive buffer
		while (WIFI_SERIAL.available()) WIFI_SERIAL.read();

		DEBUG_APPEND(cmd);
		DEBUG_APPEND(" -> ");
		DEBUG(ack);

		WIFI_SERIAL.println(cmd);

		return WIFI_SERIAL.find(ack);
	}

	bool reset() const {
		return send("AT+RST", "ready");
	}

	bool initModule() const {
		if (send("AT+CWMODE=1")) {
			if (reset()) {
				return send("AT+CIPMUX=1");
			}
		}
		return false;
	}

	bool joinAP() const {
		INFO("Try Connecting to AP..");
		char buf[128];
		sprintf(buf, "AT+CWJAP=\"%s\",\"%s\"", SSID, PW);
		
		for (int i = 0; i < AP_CONNECT_TRIES; ++i) {
			if (send(buf)) {
				INFO("Wait for AP Response..");
				if (isConnectedToAP(0)) {
					return true;
				}
				LAST_AP_CONNECTED_CHECK_MILLIS = -CHECK_AP_CONNECTED_INTERVAL;
			}
		}
		return false;
	}

	bool startServer() const {
		if (send("AT+CIPSERVER=1,80")) {
			return send("AT+CIPSTO=0");
		}
		return false;
	}

	void close(unsigned int const & channel) const {
		char buf[16];
		sprintf(buf, "AT+CIPCLOSE=%i", channel);
		send(buf);
	}

public:
	void init() const {
		WIFI_SERIAL.begin(9600);
		setTimeout(LONG_TIMEOUT);

		if (reset()) {
			INFO("Wifi Module detected!");
			WIFI_MODULE = true;
			INFO("Setup Wifi Module..");
			if (initModule()) {
				if (joinAP()) {
					INFO("Connected to AP!");
					if (startServer()) {
						INFO("Server started!");
						SERVER_RUNNING = true;
					} else {
						INFO("Server not running!");
					}
				}
			}
		} else {
			INFO("Wifi Module is not available!");
		}

		setTimeout(SHORT_TIMEOUT);
	}

	bool hasWifiModule() const {
		return WIFI_MODULE;
	}

	bool isConnectedToAP(unsigned long currentMillis) const {
		if (currentMillis - LAST_AP_CONNECTED_CHECK_MILLIS >= CHECK_AP_CONNECTED_INTERVAL || currentMillis < LAST_AP_CONNECTED_CHECK_MILLIS) {
			LAST_AP_CONNECTED_CHECK_MILLIS = currentMillis;

			char buf[62];
			sprintf(buf, "+CWJAP:\"%s\"", SSID);

			setTimeout(LONG_TIMEOUT);
			AP_CONNECTED = send("AT+CWJAP?", buf);
			resetTimeout();
		}
		return AP_CONNECTED;
	}

	bool isServerRunning() {
		return SERVER_RUNNING;
	}

	IPInfo getIPInfo() const {
		IPInfo ipInfo;

		setTimeout(LONG_TIMEOUT);
		send("AT+CIFSR", "+CIFSR:STAIP,\"");
		resetTimeout();

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

		request.length = WIFI_SERIAL.readBytesUntil('\r', request.msg, REQUEST_MSG_BUFFER);
		request.msg[request.length] = 0; // terminate string

		return request;
	}

	void response(unsigned int const & channel, char* const msg) const {
		char buf[24];
		sprintf(buf, "AT+CIPSEND=%i,%i", channel, strlen(msg));
		send(buf, ">");

		setTimeout(LONG_TIMEOUT);
		send(msg, "SEND OK");
		resetTimeout();

		close(channel);
	}
};

#endif
