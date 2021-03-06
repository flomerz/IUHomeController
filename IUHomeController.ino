// IUHomeController.ino

// Libraries
#include <Wire.h>
#include <ds3231.h>
#include <IRremote.h>
#include <SoftwareSerial.h>

// Project
#include "Logger.h"

#include "LEDDriver.h"
#include "RTCDriver.h"
#include "LDRDriver.h"

#include "RCInputController.h"
#include "MotionInputController.h"
#include "IRBarrierInputController.h"
#include "WifiInputController.h"

#include "StateMachine.h"
#include "ColorState.h"


ColorState initState(0, 0, 90);
StateMachine stateMachine(initState);

RCInputController rcInputController(stateMachine);
MotionInputController motionInputController(stateMachine);
IRBarrierInputController irBarrierInputController(stateMachine);
WifiInputController wifiInputController(stateMachine);

void setup() {
	initLogger();
	INFO("IU HOME Controller");

	// init drivers
	LED.init();
	RTC.init();
	LDR.init();

	// init input controllers
	rcInputController.init();
	motionInputController.init();
	irBarrierInputController.init();
	wifiInputController.init();
}

void loop() {
	RTC.fetchTime(millis());

	stateMachine.run();

	rcInputController.check();
	motionInputController.check();
	irBarrierInputController.check();
	wifiInputController.check();
 }
