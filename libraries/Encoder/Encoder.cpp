/* Encoder.cpp
 *
 * Class for reading ticks from quadrature encoder
 *
 * Sam McAnelly
 * Oklahoma State University
 * Spring 2019
 *
 */

#include "Encoder.h"
volatile int  Encoder::newVal = 0;
volatile int Encoder::oldVal = 0;
volatile int Encoder::outVal = 0;
volatile bool Encoder::encoder_A_set = false;
volatile bool Encoder::encoder_B_set = false;
volatile int Encoder::encoder_ticks = START_TICKS;
//Array of values to increment the encoder count
const int Encoder::matrixVal [16] = {0,-1,1,2,1,0,2,-1,-1,2,0,1,2,1,-1,0}; 

void Encoder::init()
{
    pinMode(PIN_A, INPUT_PULLUP);
    pinMode(PIN_B, INPUT_PULLUP);
	//Trigger an interrupt each time A or B rises or Falls
    attachInterrupt(digitalPinToInterrupt(PIN_A), Encoder::_tick, CHANGE); 
	attachInterrupt(digitalPinToInterrupt(PIN_B), Encoder::_tick, CHANGE);
}

int Encoder::getPosition()
{
    return encoder_ticks;
}

void Encoder::_tick()
{
	noInterrupts();
    encoder_B_set = digitalReadFast(PIN_B);
	encoder_A_set = digitalReadFast(PIN_A);
    //add 1 if A leads B
	//subtract 1 if B leads A
	//Stay contant if there is no change
	Encoder::oldVal = Encoder::newVal;
	Encoder::newVal = encoder_A_set * 2 + encoder_B_set;  
	 // Convert binary input to decimal value
	Encoder::outVal = matrixVal [Encoder::oldVal * 4 + Encoder::newVal];
	//Select appropriate matrix value to increment encoder_ticks
	if(Encoder::outVal== 1){
		encoder_ticks++;
	}
	else if(Encoder::outVal== -1){
		encoder_ticks--;
	}
	else{
	 		//do nothing
	}
	interrupts();
	
	
}

