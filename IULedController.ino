// IULedController.ino

// Libraries
#include <Wire.h>
#include <ds3231.h>
#include <IRremote.h>
#include <SoftwareSerial.h>

// Project
#include "Logger.h"

#include "StateMachine.h"
#include "ColorState.h"

#include "RCInputController.h"
#include "MotionInputController.h"
#include "IRBarrierInputController.h"
#include "WifiInputController.h"

#include "RTCHelper.h"


ColorState initState(0, 0, 90);
StateMachine stateMachine(initState);

RCInputController rcInputController(stateMachine);
MotionInputController motionInputController(stateMachine);
IRBarrierInputController irBarrierInputController(stateMachine);
WifiInputController wifiInputController(stateMachine);

void setup() {
	initLogger();
	INFO("IU LED Controller");

	// init input controllers
	rcInputController.init();
	motionInputController.init();
	irBarrierInputController.init();
	wifiInputController.init();
	
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
	wifiInputController.check();
 }
