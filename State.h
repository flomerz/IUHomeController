#ifndef STATE.H
#define STATE.H

#include "LedOutputHelper.h"

struct State {
	virtual ~State() {Serial.println("~State()");}
	
	virtual void run() {}

    virtual State & turnOff();

	virtual State & turnOn() {
		return *this;
	}
};

class OffState : public State {
	State *_oldState;
public:
	OffState(State *oldState) : _oldState(oldState) {Serial.println("OffState()");}
	
	void run() {
		Serial.println("OffState.run()");
		LedOutputHelper::setColor(0, 0, 0);
	}
	
	State & turnOn() {
		return *_oldState;
	}
};

class ColorState : public State {
	byte _red;
	byte _green;
	byte _blue;
public:
	ColorState(byte const & red, byte const & green, byte const & blue) {
		_red = red;
		_green = green;
		_blue = blue;
	}
	
	void run() {
		Serial.println("ColorState.run()");
		LedOutputHelper::setColor(_red, _green, _blue);
	}
};

#endif
