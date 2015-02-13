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

	void displayColor(byte red, byte green, byte blue) const {
		#ifdef ANODE
			red = 255 - red;
			green = 255 - green;
			blue = 255 - blue;
		#endif
		analogWrite(RED_PIN, red);
		analogWrite(GREEN_PIN, green);
		analogWrite(BLUE_PIN, blue);
	}

public:
	void init() const {
		pinMode(RED_PIN, OUTPUT);
		pinMode(GREEN_PIN, OUTPUT);
		pinMode(BLUE_PIN, OUTPUT);
		displayColor(0, 0, 0);
	}

	void setColor(byte red, byte green, byte blue) const {
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
