// IULedController.ino
#include "State.h"
#include "LedOutputHelper.h"
#include "InputController.h"

DummyInputController dummyInputController = DummyInputController();

ColorState colorState = ColorState(255, 255, 255);
OffState offState = OffState(&colorState);

State & state = colorState;

void setup() {
	Serial.begin(9600);
	LedOutputHelper::initPins();
}

void loop() {
	state = dummyInputController(state);
	delay(1000);
	state.run();
	delay(1000);
}


