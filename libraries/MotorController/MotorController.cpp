/* MotorController.cpp
 *
 * Class for using MotorControl (L298N)
 *
 * Luis Gomez
 * Oklahoma State University
 * Spring 2019
 *
 */

#include "MotorController.h"

/* DISCLAIMER, PINS = {enA,in1,in2,enB,in3,in4} */
 MotorController::MotorController()
 {
	// setPinsDefault();
 }
 
 MotorController::MotorController(int *passedPins)
 {
	 for(int i = 0; i < MC_PIN_COUNT; i++) {
		pins[i] = passedPins[i];
	}
 }
 
 void MotorController::setPinsDefault()
 {
	pins = defaultPins;
	initialize();
 }
 
 void MotorController::setPins(int *passedPins)
 {
	 
	//must make a new array if default pins were used first
	if(pins == defaultPins) {
		pins = new int[MC_PIN_COUNT];
		Serial.println("MotorController pins reset");
	}

	for(int i = 0; i < MC_PIN_COUNT; i++) {
		Serial.print("Pin number: ");
		Serial.println(passedPins[i]);
		pins[i] = passedPins[i];
	}
	Serial.println("Pins set");
	initialize();
 }
 
 
 void MotorController::initialize()
{
	for(int i = 0; i < MC_PIN_COUNT; i++) {
		pinMode(pins[i], OUTPUT);
	}
	Serial.println("Pins Initialized");
}


/*Note: Speed is a variable from 0 to 255
 *      and "forward" defines wheel rotation
 *		with respect to the the wiring 
 */
void MotorController::turnWheelA(bool forward, int speed)
{
	if(forward) {
		digitalWrite(pins[in1], HIGH);
		digitalWrite(pins[in2], LOW);
		analogWrite(pins[enA], speed);
	} else {
		digitalWrite(pins[in1], LOW);
		digitalWrite(pins[in2], HIGH);
		analogWrite(pins[enA], speed);
	}
}

void MotorController::turnWheelB(bool forward, int speed)
{
	if(forward) {
		digitalWrite(pins[in3], HIGH);
		digitalWrite(pins[in4], LOW);
		analogWrite(pins[enB], speed);
	} else {
		digitalWrite(pins[in3], LOW);
		digitalWrite(pins[in4], HIGH);
		analogWrite(pins[enB], speed);
	}
}

void MotorController::moveBothWheels(bool forward, int speed)
{
	turnWheelA(forward, speed);
	turnWheelB(forward, speed);
}

void MotorController::moveWheelsOpposite(bool turnDirection, int speed)
{
	turnWheelA(turnDirection, speed);
	turnWheelB(!turnDirection, speed);
}