#include "State.h"

State* State::turnOff() {
	State oldState = *this->clone();
	OffState *offState = new OffState(&oldState);
	return offState;
}
