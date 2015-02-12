#ifndef LEDDRIVER.H
#define LEDDRIVER.H

#include "Logger.h"


#define LED LedDriver()

#define RED_PIN 3
#define GREEN_PIN 5
#define BLUE_PIN 6

byte currentRed;
byte currentGreen;
byte currentBlue;

class LedDriver {

	void printColor() {
		INFO_APPEND("R: ");
		INFO_APPEND((int) red);
		INFO_APPEND(", G: ");
		INFO_APPEND((int) green);
		INFO_APPEND(", B: ");
		INFO((int) blue);
	}

public:
	LedDriver() {}

	void init() {
		pinMode(RED_PIN, OUTPUT);
		pinMode(GREEN_PIN, OUTPUT);
		pinMode(BLUE_PIN, OUTPUT);
	}

	void setColor(byte const & red, byte const & green, byte const & blue) {
		if (currentRed != red || currentGreen != green || currentBlue != blue) {
			currentRed = red;
			currentGreen = green;
			currentBlue = blue;

			printColor();

			analogWrite(RED_PIN, 255-red);
			analogWrite(GREEN_PIN, 255-green);
			analogWrite(BLUE_PIN, 255-blue);
		}
	}
};

#endif
