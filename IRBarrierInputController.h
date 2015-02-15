#ifndef IRBARRIERINPUTCONTROLLER.H
#define IRBARRIERINPUTCONTROLLER.H

#include "InputController.h"


#define IRBARRIER_PIN 4


class IRBarrierInputController : public InputController {

	bool on;

public:
	IRBarrierInputController(StateMachine & stateMachine) : InputController(stateMachine) {}

	void init() {
		pinMode(IRBARRIER_PIN, INPUT);
	}

	void check() {
		if (!digitalRead(IRBARRIER_PIN)) {
			_stateMachine.blockMotion();
			_stateMachine.turnOff();
		} else {
		}
	}
};

#endif
