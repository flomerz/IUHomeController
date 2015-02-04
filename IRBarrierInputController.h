#ifndef IRBARRIERINPUTCONTROLLER.H
#define IRBARRIERINPUTCONTROLLER.H

#include "InputController.h"
#include "Logger.h"


#define IRBARRIER_PIN 4


struct IRBarrierInputController : InputController {

	IRBarrierInputController(StateMachine & stateMachine) : InputController(stateMachine) {}

	void init() {
		pinMode(IRBARRIER_PIN, INPUT);
	}

	void check() {
		if (!digitalRead(IRBARRIER_PIN)) {
			_stateMachine.turnOff();
		}
	}
};

#endif
