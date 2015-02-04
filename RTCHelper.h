#ifndef RTCHELPER.H
#define RTCHELPER.H

#include <Wire.h>
#include "ds3231.h"


#define FETCH_INTERVAL 60000


struct ts lastTimestamp;
long lastFetchMillis = -FETCH_INTERVAL;

struct RTCHelper {
	
	static void init() {
		Wire.begin();
		DS3231_init(DS3231_INTCN);
	}

	static void fetchTime(unsigned long currentMillis) {
		if (currentMillis - lastFetchMillis > FETCH_INTERVAL) {
			lastFetchMillis = currentMillis;
			DS3231_get(&lastTimestamp);
			if (DEBUG) printTime();
		}
	}
	
	static unsigned int getHour() {
		return lastTimestamp.hour;
	}

	static void printTime() {
		char buff[50];
		sprintf(buff, "%02d.%02d.%d %02d:%02d:%02d", lastTimestamp.mday, lastTimestamp.mon, lastTimestamp.year, lastTimestamp.hour, lastTimestamp.min, lastTimestamp.sec);
		LOG(buff);
	}
};

#endif
