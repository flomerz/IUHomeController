#ifndef COLORSTATE.H
#define COLORSTATE.H

#include "State.h"
#include "LedOutputHelper.h"

class ColorState : public State {
	byte _red;
	byte _green;
	byte _blue;
public:
	~ColorState() {
		LOG("~ColorState()");
	}
	ColorState(byte const & red, byte const & green, byte const & blue) {
		LOG("ColorState()");
		_red = red;
		_green = green;
		_blue = blue;
	}
	State* clone() {
		LOG("ColorState.clone()");
		return new ColorState(*this);
	}
	
	// LOOP FUNCTION
	void run() {
		LOG("ColorState.run()");
		LedOutputHelper::setColor(_red, _green, _blue);
	}
};

#endif
