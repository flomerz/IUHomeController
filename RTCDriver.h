#ifndef RTCDRIVER.H
#define RTCDRIVER.H

#include <Wire.h>
#include "ds3231.h"


#define RTC RTCDriver()

#define FETCH_INTERVAL 60000


struct ts lastTimestamp;
long lastFetchMillis = -FETCH_INTERVAL;

struct RTCDriver {
	
	void init() {
		Wire.begin();
		DS3231_init(DS3231_INTCN);
	}

	void fetchTime(unsigned long currentMillis) {
		if (currentMillis - lastFetchMillis > FETCH_INTERVAL) {
			lastFetchMillis = currentMillis;
			DS3231_get(&lastTimestamp);
			printTime();
		}
	}
	
	unsigned int getHour() {
		return lastTimestamp.hour;
	}

	void printTime() {
		char buff[50];
		sprintf(buff, "%02d.%02d.%d %02d:%02d:%02d", lastTimestamp.mday, lastTimestamp.mon, lastTimestamp.year, lastTimestamp.hour, lastTimestamp.min, lastTimestamp.sec);
		INFO(buff);
	}
};

#endif