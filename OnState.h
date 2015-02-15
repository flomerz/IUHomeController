#ifndef ONSTATE.H
#define ONSTATE.H

#include "State.h"


struct OnState : State {

	bool isOn() {
		return true;
	}

	// TRIGGERS
	State* turnOn() {
		return &*this;
	}

	State* turnOff();
};

#endif
