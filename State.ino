#include "State.h"
#include "ColorState.h"


State* State::setColor(byte const & red, byte const & green, byte const & blue) {
	return new ColorState(red, green, blue);
}
