#ifndef MOTIONINPUTCONTROLLER.H
#define MOTIONINPUTCONTROLLER.H

#include "InputController.h"
#include "Logger.h"
#include "RTCHelper.h"


#define MOTION_PIN 2


class MotionInputController : public InputController {

	bool validTime() {
		unsigned int hour = RTCHelper::getHour();
		// 18:00 - 07:00
		return (hour + 7) % 24 > 0 && (hour + 7) % 24 < 14;
	}

	bool isNight() {
		unsigned int hour = RTCHelper::getHour();
		// 01:00 - 07:00
		return hour > 1 && hour < 7;
	}

public:
	MotionInputController(StateMachine & stateMachine) : InputController(stateMachine) {}

	void init() {
		pinMode(MOTION_PIN, INPUT);
	}

	void check() {
		if (_stateMachine.detectMotion()) {
			if (digitalRead(MOTION_PIN)) {
				LOG("Motion ON");
				if (validTime()) {
					LOG("Time OK");
					if(isNight()) {
						_stateMachine.setColor(0, 0, 128);
					}
					_stateMachine.turnOn();
				}
			} else {
				LOG("Motion OFF");
				_stateMachine.turnOff();
			}
		}
	}
};

#endif
