#ifndef LOGGER.H
#define LOGGER.H

bool debug = false;

void initLogger() {
	Serial.begin(9600);
}

template <typename T>
void LOG(T msg) {
	if (debug) {
		Serial.println(msg);
	}
}

template <typename T>
void INFO(T msg) {
	Serial.println(msg);
}

template <typename T>
void LOG(T msg, int format) {
	if (debug) {
		Serial.println(msg, format);
	}
}

#endif
