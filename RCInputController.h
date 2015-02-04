#ifndef RCINPUTCONTROLLER.H
#define RCINPUTCONTROLLER.H

#include "InputController.h"
#include "Logger.h"

#include <IRremote.h>

#define IR_PIN 11

#define RED_MASK 0xFF0000
#define GREEN_MASK 0x00FF00
#define BLUE_MASK 0x0000FF

// KEYS
#define KEY_ON 0xFF02FD
#define KEY_RED 0xFF1AE5
#define KEY_GREEN 0xFF9A65
#define KEY_BLUE 0xFFA25D

// COLORS
#define RED 0xFF0000
#define GREEN 0x00FF00
#define BLUE 0x0000FF

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
