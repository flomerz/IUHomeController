// IULedController.ino
#include "StateMachine.h"
#include "InputController.h"
#include "LedOutputHelper.h"

DummyInputController dummyInputController = DummyInputController();

StateMachine stateMachine = StateMachine();

void setup() {
	Serial.begin(9600);
	LedOutputHelper::initPins();
}

void loop() {
	//dummyInputController(state);
	stateMachine.turnOn();
	stateMachine.run();
	delay(1000);

	stateMachine.turnOff();
	stateMachine.run();
	delay(1000);
}


