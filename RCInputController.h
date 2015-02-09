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
				case KEY_1:	_stateMachine.turnLighter(); break;
				case KEY_2:	_stateMachine.turnDarker(); break;
				case KEY_3:	_stateMachine.unblockMotion(); break;
				case KEY_4:	_stateMachine.blockMotion(); _stateMachine.toggleOn(); break;
				
				case KEY_5: setColor(RED); break;
				case KEY_6: setColor(GREEN); break;
				case KEY_7: setColor(BLUE);	break;
				case KEY_8: setColor(WHITE); break;
				
				case KEY_9: setColor(LIGHTRED); break;
				case KEY_10: setColor(LIGHTGREEN); break;
				case KEY_11: setColor(LIGHTBLUE); break;
				case KEY_12: setColor(PINK); break;
				
				case KEY_13: setColor(ORANGE); break;
				case KEY_14: setColor(CYAN); break;
				case KEY_15: setColor(PURPLE); break;
				case KEY_16: setColor(LIGHTPINK); break;

				case KEY_25: LOG("RED UP"); _stateMachine.turnRedLighter(); break;
				case KEY_26: LOG("GREEN UP"); _stateMachine.turnGreenLighter(); break;
				case KEY_27: LOG("BLUE UP"); _stateMachine.turnBlueLighter(); break;

				case KEY_29: _stateMachine.turnRedDarker(); break;
				case KEY_30: _stateMachine.turnGreenDarker(); break;
				case KEY_31: _stateMachine.turnBlueDarker(); break;
			}
			irReceiver.resume();
		}
	}
};

#endif
