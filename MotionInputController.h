#ifndef MOTIONINPUTCONTROLLER.H
#define MOTIONINPUTCONTROLLER.H

#include "InputController.h"
#include "Logger.h"

#define MOTION_PIN 2

struct MotionInputController : InputController {
	MotionInputController(StateMachine & stateMachine) : InputController(stateMachine) {}
	void init() {
		pinMode(MOTION_PIN, INPUT);
	}
	void check() {
		if (digitalRead(MOTION_PIN)) {
			_stateMachine.turnOn();
		} else {
			_stateMachine.turnOff();
		}
	}
};

#endif
