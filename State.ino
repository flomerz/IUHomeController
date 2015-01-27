#include "State.h"

State & State::turnOff() {
	Serial.println("turnOff()");

	State & oldState = *this;
	OffState offState = OffState(&oldState);

	State & r = offState;
	r.run();
	return r;
}
