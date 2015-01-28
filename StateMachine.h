#ifndef STATEMACHINE.H
#define STATEMACHINE.H

#include "State.h"

class StateMachine {
	State *_state;
	void setState(State* state) {
		if(_state != state) {
			delete(_state);
			_state = state;
		}
	}
public:
	StateMachine() {
		ColorState *colorState = new ColorState(255, 255, 255);
		_state = colorState;
	}
	void run() {
		_state->run();
	}

	void turnOff() {
		setState(_state->turnOff());
	};

	void turnOn() {
		setState(_state->turnOn());
	}
};

#endif
