// IULedController.ino
#include <IRremote.h>

#include "Logger.h"

#include "StateMachine.h"
#include "ColorState.h"

#include "RCInputController.h"

ColorState initState(255, 255, 255);
StateMachine stateMachine(initState);

DummyInputController dummyInputController(stateMachine);
RCInputController rcInputController(stateMachine);

void setup() {
	initLogger();
	rcInputController.init();
	LedOutputHelper::init();
}

void loop() {
	rcInputController.check();
	stateMachine.run();
	delay(1000);
}
