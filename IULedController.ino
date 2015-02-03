// IULedController.ino
#include "Logger.h"

#include "StateMachine.h"
#include "ColorState.h"

#include "RCInputController.h"

DummyInputController dummyInputController = DummyInputController();
RCInputController rcInputController = RCInputController();

ColorState initState = ColorState(255, 255, 255);
StateMachine stateMachine = StateMachine(initState);

void setup() {
	initLogger();
	LedOutputHelper::initPins();
}

void loop() {
	dummyInputController(stateMachine);
	stateMachine.turnOn();
	stateMachine.run();
	// delay(10);

	rcInputController(stateMachine);
	stateMachine.run();
	// delay(10);

	stateMachine.turnOff();
	stateMachine.run();
	// delay(10);
}
