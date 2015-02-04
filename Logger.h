#ifndef LOGGER.H
#define LOGGER.H

#define DEBUG false

void initLogger() {
	Serial.begin(9600);
}

template <typename T>
void LOG(T msg) {
	if (DEBUG) {
		Serial.println(msg);
	}
}

template <typename T>
void INFO(T msg) {
	Serial.println(msg);
}

template <typename T>
void LOG(T msg, int format) {
	if (DEBUG) {
		Serial.println(msg, format);
	}
}

#endif
