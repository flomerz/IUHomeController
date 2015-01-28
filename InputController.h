#ifndef INPUTCONTROLLER.H
#define INPUTCONTROLLER.H

#include "StateMachine.h"

struct InputController {
	virtual void operator()(StateMachine &stateMachine)=0;
};

struct DummyInputController : InputController{
	void operator()(StateMachine &stateMachine) {
		stateMachine.turnOff();
	}
};

#endif
