#ifndef INPUTCONTROLLER.H
#define INPUTCONTROLLER.H

#include "State.h"

struct InputController {
	virtual State & operator()(State & state)=0;
};

struct DummyInputController : InputController{
	State & operator()(State & state) {
		return state.turnOff();
	}
};

#endif
