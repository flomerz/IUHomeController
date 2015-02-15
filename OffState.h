#ifndef OFFSTATE.H
#define OFFSTATE.H

#include "State.h"
#include "LEDDriver.h"


class OffState : public State {

	State *_oldState;

public:
	~OffState() {
		delete(_oldState);
	}

	OffState(State *oldState) {
		_oldState = oldState;
	}

	State* clone() {
		return new OffState(*this);
	}

	bool isOn() {
		return false;
	}


	// LOOP FUNCTION
	void run() {
		LED.setColor(0, 0, 0);
	}


	// TRIGGERS
	State* turnOff() {
		return &*this;
	}

	State* turnOn() {
		State* oldState = _oldState;
		_oldState = 0;
		return oldState;
	}
};

#endif
