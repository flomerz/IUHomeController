 #ifndef RCINPUTCONTROLLER.H
#define RCINPUTCONTROLLER.H

#include "InputController.h"
#include "Logger.h"

#include <IRremote.h>

// KEYS
#include "RC44.h"
// COLORS
#include "Colors.h"

/*
 VCC to 5V
 GND to GND
 OUT to IR_PIN
*/

#define IR_PIN 7


IRrecv irReceiver(IR_PIN);
decode_results irResults;

struct RCInputController : InputController {

	RCInputController(StateMachine & stateMachine) : InputController(stateMachine) {}

	void init() {
		irReceiver.enableIRIn();
	}

	void check() {
		if (irReceiver.decode(&irResults)) {
			INFO(irResults.value, HEX);
			switch(irResults.value) {
				case KEY_1:	_stateMachine.turnLighter(); break;
				case KEY_2:	_stateMachine.turnDarker(); break;
				case KEY_3:	_stateMachine.unblockMotion(); break;
				case KEY_4:	_stateMachine.blockMotion(); _stateMachine.toggleOn(); break;
				
				case KEY_5: _stateMachine.setColor(RED); break;
				case KEY_6: _stateMachine.setColor(GREEN); break;
				case KEY_7: _stateMachine.setColor(BLUE);	break;
				case KEY_8: _stateMachine.setColor(WHITE); break;
				
				case KEY_9: _stateMachine.setColor(LIGHTRED); break;
				case KEY_10: _stateMachine.setColor(LIGHTGREEN); break;
				case KEY_11: _stateMachine.setColor(LIGHTBLUE); break;
				case KEY_12: _stateMachine.setColor(PINK); break;
				
				case KEY_13: _stateMachine.setColor(ORANGE); break;
				case KEY_14: _stateMachine.setColor(CYAN); break;
				case KEY_15: _stateMachine.setColor(PURPLE); break;
				case KEY_16: _stateMachine.setColor(LIGHTPINK); break;

				case KEY_25: _stateMachine.turnRedLighter(); break;
				case KEY_26: _stateMachine.turnGreenLighter(); break;
				case KEY_27: _stateMachine.turnBlueLighter(); break;

				case KEY_29: _stateMachine.turnRedDarker(); break;
				case KEY_30: _stateMachine.turnGreenDarker(); break;
				case KEY_31: _stateMachine.turnBlueDarker(); break;
			}
			irReceiver.resume();
		}
	}
};

#endif
