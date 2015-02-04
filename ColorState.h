#ifndef COLORSTATE.H
#define COLORSTATE.H

#include "State.h"
#include "LedOutputHelper.h"

class ColorState : public State {
	byte _red;
	byte _green;
	byte _blue;

	int intensivity;
	byte currentRed;
	byte currentGreen;
	byte currentBlue;

	void turnBrightness() {
		currentRed = min(_red * pow(2, intensivity), 255);
		currentGreen = min(_green * pow(2, intensivity), 255);
		currentBlue = min(_blue * pow(2, intensivity), 255);
	}
public:
	~ColorState() {
		LOG("~ColorState()");
	}
	ColorState(byte const & red, byte const & green, byte const & blue) {
		LOG("ColorState()");
		_red = red;
		_green = green;
		_blue = blue;

		intensivity = 0;
		currentRed = red;
		currentGreen = green;
		currentBlue = blue;
	}
	State* clone() {
		LOG("ColorState.clone()");
		return new ColorState(*this);
	}
	
	// LOOP FUNCTION
	void run() {
		LOG("ColorState.run()");
		LedOutputHelper::setColor(currentRed, currentGreen, currentBlue);
	}

	// TRIGGERS
	void turnLighter() {
		intensivity += intensivity < 8 ? 1 : 0;
		turnBrightness();
	}
	void turnDarker() {
		intensivity -= intensivity > -8 ? 1 : 0;
		turnBrightness();
	}
};

#endif
