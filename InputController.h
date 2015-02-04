#ifndef INPUTCONTROLLER.H
#define INPUTCONTROLLER.H

#include "StateMachine.h"

class InputController {
protected:
	StateMachine &_stateMachine;
public:
	InputController(StateMachine & stateMachine) : _stateMachine(stateMachine) {}
	virtual void check()=0;
};

struct DummyInputController : InputController{
	DummyInputController(StateMachine & stateMachine) : InputController(stateMachine) {}
	void check() {
		_stateMachine.turnOn();
	}
};

#endif
