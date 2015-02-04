#ifndef OFFSTATE.H
#define OFFSTATE.H

#include "State.h"
#include "LedOutputHelper.h"

class OffState : public State {
	State *_oldState;
public:
	~OffState() {
		LOG("~OffState()");
		delete(_oldState);
	}
	OffState(State *oldState) {
		LOG("OffState()");
		_oldState = oldState;
	}
	State* clone() {
		LOG("OffState.clone()");
		return new OffState(*this);
	}

	bool isOn() {
		return false;
	}
	
	// LOOP FUNCTION
	void run() {
		LOG("OffState.run()");
		LedOutputHelper::setColor(0, 0, 0);
	}
	
	// TRIGGERS
	State* turnOff() {
		LOG("OffState.turnOff()");
		return &*this;
	}
	State* turnOn() {
		LOG("OffState.turnOn()");
		State* oldState = _oldState;
		_oldState = 0;
		return oldState;
	}
};

#endif
