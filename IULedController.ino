// IULedController.ino

// Libraries
#include <Wire.h>
#include <ds3231.h>
#include <IRremote.h>

// Project
#include "Logger.h"

#include "StateMachine.h"
#include "ColorState.h"

#include "RCInputController.h"
#include "MotionInputController.h"
#include "IRBarrierInputController.h"

#include "RTCHelper.h"


ColorState initState(255, 255, 255);
StateMachine stateMachine(initState);

RCInputController rcInputController(stateMachine);
MotionInputController motionInputController(stateMachine);
IRBarrierInputController irBarrierInputController(stateMachine);

void setup() {
	initLogger();

	// init input controllers
	rcInputController.init();
	motionInputController.init();
	irBarrierInputController.init();
	
	// init helper
	LedOutputHelper::init();
	RTCHelper::init();
}

void loop() {
	RTCHelper::fetchTime(millis());

	stateMachine.run();

	rcInputController.check();
	motionInputController.check();
	irBarrierInputController.check();
 }
