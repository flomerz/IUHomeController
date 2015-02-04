#ifndef STATEMACHINE.H
#define STATEMACHINE.H

#include "Logger.h"
#include "State.h"


#define MOTION_BLOCK_MILLIS 60000


class StateMachine {

	State *_state;

	unsigned long motionBlockMillis;

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
		unblockMotion();
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

	void turnLighter() {
		_state->turnLighter();
	}

	void turnDarker() {
		_state->turnDarker();
	}

	void blockMotion() {
		motionBlockMillis = millis();
	}

	void unblockMotion() {
		motionBlockMillis = -MOTION_BLOCK_MILLIS;
	}

	bool detectMotion() {
		return millis() - motionBlockMillis > MOTION_BLOCK_MILLIS; 
	}
};

#endif
