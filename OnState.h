#ifndef ONSTATE.H
#define ONSTATE.H

#include "State.h"


struct OnState : State {

	bool isOn() {
		return true;
	}

	// TRIGGERS
	State* turnOn() {
		DEBUG("OnState.turnOn()");
		return &*this;
	}

	State* turnOff();
};

#endif
