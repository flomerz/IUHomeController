#ifndef LOGGER.H
#define LOGGER.H

#include <SoftwareSerial.h>

#define RX_PIN 8
#define TX_PIN 12


#define LOG_SERIAL logSerial

// #define LOG_DEBUG
#define LOG_INFO


SoftwareSerial logSerial(RX_PIN, TX_PIN);

void initLogger() {
	logSerial.begin(9600);
}

template <typename T>
void LOG(T msg) {
	logSerial.println(msg);
}

template <typename T>
void LOG_APPEND(T msg) {
	logSerial.print(msg);
}

template <typename T>
void LOG(T msg, int format) {
	logSerial.println(msg, format);
}

template <typename T>
void INFO(T msg) {
	#ifdef LOG_INFO
		LOG(msg);
	#endif
}

template <typename T>
void INFO_APPEND(T msg) {
	#ifdef LOG_INFO
		LOG_APPEND(msg);
	#endif
}

template <typename T>
void INFO(T msg, int format) {
	#ifdef LOG_INFO
		LOG(msg, format);
	#endif
}

template <typename T>
void DEBUG(T msg) {
	#ifdef LOG_DEBUG
		LOG(msg);
	#endif
}

template <typename T>
void DEBUG_APPEND(T msg) {
	#ifdef LOG_DEBUG
		LOG_APPEND(msg);
	#endif
}

template <typename T>
void DEBUG(T msg, int format) {
	#ifdef LOG_DEBUG
		LOG(msg, format);
	#endif
}

#endif
