#ifndef RCINPUTCONTROLLER.H
#define RCINPUTCONTROLLER.H

#include "InputController.h"
#include "Logger.h"

#include <IRremote.h>

// KEYS
#include "RC44.h"
// COLORS
#include "Colors.h"

#define IR_PIN 10

#define RED_MASK 0xFF0000
#define GREEN_MASK 0x00FF00
#define BLUE_MASK 0x0000FF

IRrecv irReceiver(IR_PIN);
decode_results irResults;

class RCInputController : public InputController {
	void setColor(long color) {
		byte red = (RED_MASK & color) >> 16;
		byte green = (GREEN_MASK & color) >> 8;
		byte blue = BLUE_MASK & color;

		_stateMachine.setColor(red, green, blue);
	}
public:
	RCInputController(StateMachine & stateMachine) : InputController(stateMachine) {}
	void init() {
		irReceiver.enableIRIn();
	}
	void check() {
		if (irReceiver.decode(&irResults)) {
			LOG(irResults.value, HEX);
			switch(irResults.value) {
				case KEY_ON:
					_stateMachine.toggleOn();
					break;
				case KEY_RED:
					setColor(RED);
					break;
				case KEY_GREEN:
					setColor(GREEN);
					break;
				case KEY_BLUE:
					setColor(BLUE);
					break;
			}
			irReceiver.resume();
		}
	}
};

#endif
