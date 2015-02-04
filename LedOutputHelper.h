#ifndef LEDOUTPUTHELPER.H
#define LEDOUTPUTHELPER.H

#include "Logger.h"


#define RED_PIN 5
#define GREEN_PIN 3
#define BLUE_PIN 6


byte currentRed;
byte currentGreen;
byte currentBlue;

struct LedOutputHelper {

	static void init() {
		pinMode(RED_PIN, OUTPUT);
		pinMode(GREEN_PIN, OUTPUT);
		pinMode(BLUE_PIN, OUTPUT);
	}

	static void setColor(byte const & red, byte const & green, byte const & blue) {
		if (currentRed != red || currentGreen != green || currentBlue != blue) {
			currentRed = red;
			currentGreen = green;
			currentBlue = blue;

			char colorStr[32];
			sprintf(colorStr, "R: %i, G: %i, B: %i\0", red, green, blue);
			LOG(colorStr);
			
			analogWrite(RED_PIN, 255-red);
			analogWrite(GREEN_PIN, 255-green);
			analogWrite(BLUE_PIN, 255-blue);
		}
	}
};

#endif
