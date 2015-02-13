#ifndef LEDDRIVER.H
#define LEDDRIVER.H

#include "Logger.h"


#define LED LEDDriver()

#define RED_PIN 3
#define GREEN_PIN 5
#define BLUE_PIN 6

#define ANODE

byte currentRed;
byte currentGreen;
byte currentBlue;

class LEDDriver {

	void printColor() const {
		INFO_APPEND("R: ");
		INFO_APPEND((int) currentRed);
		INFO_APPEND(", G: ");
		INFO_APPEND((int) currentGreen);
		INFO_APPEND(", B: ");
		INFO((int) currentBlue);
	}

	void displayColor(byte const & red, byte const & green, byte const & blue) const {
		#ifdef ANODE
			analogWrite(RED_PIN, 255 - red);
			analogWrite(GREEN_PIN, 255 - green);
			analogWrite(BLUE_PIN, 255 - blue);
		#elif
			analogWrite(RED_PIN, red);
			analogWrite(GREEN_PIN, green);
			analogWrite(BLUE_PIN, blue);
		#endif
	}

public:
	void init() const {
		pinMode(RED_PIN, OUTPUT);
		pinMode(GREEN_PIN, OUTPUT);
		pinMode(BLUE_PIN, OUTPUT);
		displayColor(0, 0, 0);
	}

	void setColor(byte const & red, byte const & green, byte const & blue) const {
		if (currentRed != red || currentGreen != green || currentBlue != blue) {
			currentRed = red;
			currentGreen = green;
			currentBlue = blue;

			printColor();
			displayColor(red, green, blue);
		}
	}
};

#endif
