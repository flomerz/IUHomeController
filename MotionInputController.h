#ifndef MOTIONINPUTCONTROLLER.H
#define MOTIONINPUTCONTROLLER.H

#include "InputController.h"
#include "Logger.h"
#include "RTCDriver.h"
#include "LDRDriver.h"
#include "Colors.h"


/*
 GND to GND
 VCC to 5V
 OUT to MOTION_PIN
*/

#define MOTION_PIN 2


class MotionInputController : public InputController {

	bool on;

	bool validTime() {
		unsigned int hour = RTC.getHour();
		// 18:00 - 07:00
		return (hour + 7) % 24 > 0 && (hour + 7) % 24 < 14;
	}

	bool isNight() {
		unsigned int hour = RTC.getHour();
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
				if(validTime() && LDR.isDark()) {
					if (!on) INFO("Motion - ON"); on = true;
					if(isNight()) {
						DEBUG("Motion - Night");
						_stateMachine.setColor(NIGHTBLUE);
					}
					_stateMachine.turnOn();
				}
			} else {
				if (on) INFO("Motion - OFF"); on = false;
				_stateMachine.turnOff();
			}
		}
	}
};

#endif
