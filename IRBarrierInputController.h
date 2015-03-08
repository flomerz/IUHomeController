#ifndef IRBARRIERINPUTCONTROLLER.H
#define IRBARRIERINPUTCONTROLLER.H

#include "InputController.h"
#include "Logger.h"

/*
 GND to GND
 OUT to IRBARRIER_PIN
 VCC to 5V
*/

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
			if (on) INFO("IR Barrier - OFF"); on = false;
			_stateMachine.blockMotion();
			_stateMachine.turnOff();
		} else {
			if (!on) INFO("IR Barrier - ON"); on = true;
		}
	}
};

#endif
