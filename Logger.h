#ifndef LOGGER.H
#define LOGGER.H

bool debug = true;

void initLogger() {
	Serial.begin(9600);
}

void LOG(char * msg) {
	if (debug) {
		Serial.println(msg);
	}
}

#endif
