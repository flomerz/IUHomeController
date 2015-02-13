#ifndef OFFSTATE.H
#define OFFSTATE.H

#include "State.h"
#include "LEDDriver.h"


class OffState : public State {

	State *_oldState;

public:
	~OffState() {
		DEBUG("~OffState()");
		delete(_oldState);
	}

	OffState(State *oldState) {
		DEBUG("OffState()");
		_oldState = oldState;
	}

	State* clone() {
		DEBUG("OffState.clone()");
		return new OffState(*this);
	}

	bool isOn() {
		return false;
	}


	// LOOP FUNCTION
	void run() {
		// DEBUG("OffState.run()");
		LED.setColor(0, 0, 0);
	}


	// TRIGGERS
	State* turnOff() {
		DEBUG("OffState.turnOff()");
		return &*this;
	}

	State* turnOn() {
		DEBUG("OffState.turnOn()");
		State* oldState = _oldState;
		_oldState = 0;
		return oldState;
	}
};

#endif
