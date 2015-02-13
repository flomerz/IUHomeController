#ifndef STATEMACHINE.H
#define STATEMACHINE.H

#include "Logger.h"
#include "State.h"
#include "Colors.h"


#define MOTION_BLOCK_MILLIS 60000


class StateMachine {

	State *_state;

	unsigned long motionBlockMillis;

	void setState(State* state) {
		if(_state != state) {
			DEBUG("StateMachine.delete()");
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
		DEBUG("StateMachine.turnOff()");
		setState(_state->turnOff());
	}

	void turnOn() {
		DEBUG("StateMachine.turnOn()");
		setState(_state->turnOn());
	}

	void toggleOn() {
		DEBUG("StateMachine.toggleOn()");
		if (_state->isOn()) {
			turnOff();
		} else {
			turnOn();
		}
	}

	void setColor(byte const & red, byte const & green, byte const & blue) {
		setState(_state->setColor(red, green, blue));
	}

	void setColor(long rgb) {
		setColor(red(rgb), green(rgb), blue(rgb));
	}

	void turnLighter() {
		_state->turnLighter();
	}
	void turnRedLighter() {
		_state->turnRedLighter();
	}
	void turnGreenLighter() {
		_state->turnGreenLighter();
	}
	void turnBlueLighter() {
		_state->turnBlueLighter();
	}

	void turnDarker() {
		_state->turnDarker();
	}
	void turnRedDarker() {
		_state->turnRedDarker();
	}
	void turnGreenDarker() {
		_state->turnGreenDarker();
	}
	void turnBlueDarker() {
		_state->turnBlueDarker();
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
