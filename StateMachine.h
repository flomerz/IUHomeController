#ifndef STATEMACHINE.H
#define STATEMACHINE.H

#include "Logger.h"
#include "State.h"

class StateMachine {
	State *_state;
	void setState(State* state) {
		if(_state != state) {
			LOG("StateMachine.delete()");
			delete(_state);
			_state = state;
		}
	}
public:
	StateMachine(State & initState) {
		_state = initState.clone();
	}
	void run() {
		_state->run();
	}

	void turnOff() {
		LOG("StateMachine.turnOff()");
		setState(_state->turnOff());
	}
	void turnOn() {
		LOG("StateMachine.turnOn()");
		setState(_state->turnOn());
	}
	void toggleOn() {
		if (_state->isOn()) {
			turnOff();
		} else {
			turnOn();
		}
	}
	void setColor(byte const & red, byte const & green, byte const & blue) {
		setState(_state->setColor(red, green, blue));
	}
};

#endif
