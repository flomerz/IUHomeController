#include "State.h"
#include "OffState.h"
#include "ColorState.h"


State* State::turnOff() {
	LOG("State.turnOff()");
	State *oldState = &*this;
	State *oldStateClone = oldState->clone();
	return new OffState(oldStateClone);
}

State* State::setColor(byte const & red, byte const & green, byte const & blue) {
	LOG("State.setColor()");
	return new ColorState(red, green, blue);
}