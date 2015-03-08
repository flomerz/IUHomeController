#ifndef LDRDRIVER.H
#define LDRDRIVER.H

#include <Wire.h>
#include "ds3231.h"


#define LDR LDRDriver()

/*
 PIN 1 to 5V
 PIN 2 to LDR_PIN and (10k Ohm to GND)
*/

#define LDR_PIN A0
#define THRESHOLD 300


struct LDRDriver {
	
	void init() const {
		pinMode(LDR_PIN, INPUT);
	}

	bool isDark() {
		return analogRead(LDR_PIN) < THRESHOLD;
	}

};

#endif
