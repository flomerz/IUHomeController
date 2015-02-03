#ifndef RCINPUTCONTROLLER.H
#define RCINPUTCONTROLLER.H

#include "InputController.h"

#define RED_MASK 0xFF0000
#define GREEN_MASK 0x00FF00
#define BLUE_MASK 0x0000FF

#define RED 0x400000

struct RCInputController : InputController{
	void operator()(StateMachine &stateMachine) {
		long color = RED;

		byte red = (RED_MASK & color) >> 16;
		byte green = (GREEN_MASK & color) >> 8;
		byte blue = BLUE_MASK & color;

		stateMachine.setColor(red, green, blue);
	}
};

#endif
