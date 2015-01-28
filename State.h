#ifndef STATE.H
#define STATE.H

#include "LedOutputHelper.h"

struct State {
	virtual ~State() {}
	virtual State* clone() {
		return new State(*this);
	}
	
	virtual void run() {}

	virtual State* turnOff();

	virtual State* turnOn() {
		return &*this;
	}
};

class OffState : public State {
	State *_oldState;
public:
	virtual ~OffState() {Serial.println("~OffState()");
}
	OffState(State *oldState) {
		Serial.println("OffState()");
		_oldState = oldState;
	}
	virtual State* clone() {
		Serial.println("OffState.clone()");
		return new OffState(*this);
	}
	
	void run() {
		Serial.println("OffState.run()");
		LedOutputHelper::setColor(0, 0, 0);
	}
	
	State* turnOn() {
		return _oldState;
	}
};

class ColorState : public State {
	byte _red;
	byte _green;
	byte _blue;
public:
	virtual ~ColorState() {Serial.println("~ColorState()");}
	ColorState(byte const & red, byte const & green, byte const & blue) {
		_red = red;
		_green = green;
		_blue = blue;
	}
	virtual State* clone() {
		Serial.println("ColorState.clone()");
		return new ColorState(*this);
	}
	
	void run() {
		Serial.println("ColorState.run()");
		LedOutputHelper::setColor(_red, _green, _blue);
	}
};

#endif
