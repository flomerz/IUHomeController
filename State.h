#ifndef STATE.H
#define STATE.H

#include "Logger.h"


struct State {

	virtual ~State() {
		LOG("~State()");
	}

	State() {
		LOG("State()");
	}

	virtual State* clone()=0;

	virtual bool isOn() {
		return true;
	}


	// LOOP FUNCTION
	virtual void run()=0;


	// TRIGGERS
	virtual State* turnOff();

	virtual State* turnOn() {
		LOG("State.turnOn()");
		return &*this;
	}

	virtual State* setColor(byte const & red, byte const & green, byte const & blue);

	virtual void turnLighter() {}
	virtual void turnRedLighter() {}
	virtual void turnGreenLighter() {}
	virtual void turnBlueLighter() {}

	virtual void turnDarker() {}
	virtual void turnRedDarker() {}
	virtual void turnGreenDarker() {}
	virtual void turnBlueDarker() {}
};

#endif
