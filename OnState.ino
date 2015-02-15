#include "OnState.h"
#include "OffState.h"
#include "ColorState.h"


State* OnState::turnOff() {
	DEBUG("OnState.turnOff()");
	State *oldState = &*this;
	State *oldStateClone = oldState->clone();
	return new OffState(oldStateClone);
}
