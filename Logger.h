#ifndef LOGGER.H
#define LOGGER.H

#include <SoftwareSerial.h>

#define RX_PIN 13
#define TX_PIN 12


#define DEBUG false


SoftwareSerial logSerial(RX_PIN, TX_PIN);

void initLogger() {
	logSerial.begin(9600);
}

template <typename T>
void LOG(T msg) {
	if (DEBUG) {
		logSerial.println(msg);
	}
}

template <typename T>
void INFO(T msg) {
	logSerial.println(msg);
}

template <typename T>
void LOG(T msg, int format) {
	if (DEBUG) {
		logSerial.println(msg, format);
	}
}

#endif
