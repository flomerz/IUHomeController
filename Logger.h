#ifndef LOGGER.H
#define LOGGER.H

#include <SoftwareSerial.h>

#define RX_PIN 13
#define TX_PIN 12


#define LOG_SERIAL logSerial

// #define DEBUG


SoftwareSerial logSerial(RX_PIN, TX_PIN);

void initLogger() {
	logSerial.begin(9600);
}

template <typename T>
void LOG_APPEND(T msg) {
	#ifdef DEBUG
		logSerial.print(msg);
	#endif
}

template <typename T>
void LOG(T msg) {
	#ifdef DEBUG
		logSerial.println(msg);
	#endif
}

template <typename T>
void LOG(T msg, int format) {
	#ifdef DEBUG
		logSerial.println(msg, format);
	#endif
}

template <typename T>
void INFO_APPEND(T msg) {
	logSerial.print(msg);
}

template <typename T>
void INFO(T msg) {
	logSerial.println(msg);
}

template <typename T>
void INFO(T msg, int format) {
	logSerial.println(msg, format);
}

#endif
