#ifndef LOGGER.H
#define LOGGER.H

bool debug = true;

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
void LOG(T msg, int format) {
	if (debug) {
		Serial.println(msg, format);
	}
}

#endif
