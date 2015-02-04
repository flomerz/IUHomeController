// IULedController.ino
#include <IRremote.h>

#include "Logger.h"

#include "StateMachine.h"
#include "ColorState.h"

#include "RCInputController.h"
#include "MotionInputController.h"
#include "IRBarrierInputController.h"

ColorState initState(255, 255, 255);
StateMachine stateMachine(initState);

RCInputController rcInputController(stateMachine);
MotionInputController motionInputController(stateMachine);
IRBarrierInputController irBarrierInputController(stateMachine);

void setup() {
	initLogger();

	// init input controllers
	rcInputController.init();
	motionInputController.init();
	irBarrierInputController.init();
	
	// init output
	LedOutputHelper::init();
}

void loop() {
	rcInputController.check();
	motionInputController.check();
	irBarrierInputController.check();

	stateMachine.run();
}
