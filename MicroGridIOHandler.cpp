#include "MicroGridIOHandler.h"

#include <asiodnp3/MeasUpdate.h>
#include <iostream>
#include <chrono>
#include <wiringPi.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>

using namespace opendnp3;
using namespace asiodnp3;

// better for loops
#define REP(i,a,b)      for (int i = int(a); i < int(b); i++)

// these will be the pins which model faults for each circuit
#define FAULTMASTER 0
#define FAULT1 1
#define FAULT2 2
#define FAULT3 3
#define FAULT4 4
#define FAULT5 5
#define FAULT6 6

// these will be the pins for the on/off buttons for each circuit 
#define BUTTONMASTER 7
#define BUTTON1 8
#define BUTTON2 9
#define BUTTON3 10
#define BUTTON4 11
#define BUTTON5 12
#define BUTTON6 13

// these pins will enable/disable the relays
#define RELAYMASTER 14
#define RELAY1 15
#define RELAY2 16
#define RELAY3 17
#define RELAY4 18
#define RELAY5 19
#define RELAY6 20

// these pins will monitor the status of each relay
#define STATUSMASTER 21
#define STATUS1 22
#define STATUS2 23
#define STATUS3 24
#define STATUS4 25
#define STATUS5 26
#define STATUS6 27

void microgridIOHandler::microgrid_init(void)
{
	wiringPiSetup();
	
	pinMode(FAULTMASTER, INPUT);
	pinMode(FAULT1, INPUT);
	pinMode(FAULT2, INPUT);
	pinMode(FAULT3, INPUT);
	pinMode(FAULT4, INPUT);
	pinMode(FAULT5, INPUT);
	pinMode(FAULT6, INPUT);
	
	pinMode(BUTTONMASTER, INPUT);
	pinMode(BUTTON1, INPUT);
	pinMode(BUTTON2, INPUT);
	pinMode(BUTTON3, INPUT);
	pinMode(BUTTON4, INPUT);
	pinMode(BUTTON5, INPUT);
	pinMode(BUTTON6, INPUT);
	
	pinMode(RELAYMASTER, OUTPUT);
	pinMode(RELAY1, OUTPUT);
	pinMode(RELAY2, OUTPUT);
	pinMode(RELAY3, OUTPUT);
	pinMode(RELAY4, OUTPUT);
	pinMode(RELAY5, OUTPUT);
	pinMode(RELAY6, OUTPUT);
	
	pinMode(STATUSMASTER, INPUT);
	pinMode(STATUS1, INPUT);
	pinMode(STATUS2, INPUT);
	pinMode(STATUS3, INPUT);
	pinMode(STATUS5, INPUT);
	pinMode(STATUS5, INPUT);
	pinMode(STATUS6, INPUT);
}
void microgridIOHandler::doOperate(const ControlRelayOutputBlock& command, uint_8 index)
{
	uint_8 value = (command.functionCode == ControlCode::LATCH_ON) ? 1 : 0;
	writeSwitchValue(index, value);
}

CommandStatus microgridIOHandler::validateCROB(const ControlRelayOutputBlock& command, uint_16 index)
{
	switch(command.functionCode)
	{
		case(ControlCode::LATCH_ON)
		case(ControlCode::LATCH_OFF)
			return CommandStatus::SUCCESS;
		default:
			return CommandStatus::NOT_SUPPORTED;
	}
}

void microgridIOHandler::writeSwitchValue(uint8_t index, bool value)
{
	piLock(2);
	this.microgrid.fault[index] = value;
	piUnlock(2);
}

// the following two fxns may not be necessary
void microgridIOHandler::write_button_value(uint8_t index, bool value)
{
	
}

void microgridIOHandler::write_relay_value(uint8_t index, bool value)
{
	
}

// initialize button interrupt handler
void microgridIOHandler::button_interrupt(uint8_t index)
{
	piLock(0);
	this.microgrid.floor[index] = !this.microgrid.floor[index];
	piUnlock(0);
}

// initialize interrupt relay interrupt handler
void microgridIOHandler::relay_interrupt(uint8_t index)
{
	piLock(1);
	this.microgrid.relay[index] = !this.microgrid.relay[index];
	piUnlock(1);
}


/* helper function for interrupt handling
   using interrupts will eliminate the need to hack a delay into our code
   to account for the relay latency */

void microgridIOHandler::thread_starter(void)
{
	REP( i, BUTTONMASTER, (BUTTON6 + 1) ) // create interrupt for each button
	{
		if ( !wiringPiISR( i, INT_EDGE_BOTH, &buttonInterrupt (i - BUTTONMASTER) ) )
		{
			fprintf( stderr, "Thread not started!", strerror (errno) );
			return 1;
		}
	}
	
	// this will eliminate the need to hack a delay into our code.
	REP( i, RELAYMASTER, (RELAY6 + 1) ) // create interrupt for each relay
		if ( !wiringPiISR( i, INT_EDGE_BOTH, &relayInterrupt (i - RELAYMASTER) ) )
		{
			fprintf( stderr, "Thread not started!", strerror (errno) );
			return 1;
		}
	}
}

// write fxn to switch relay status based on button presses

// write fxn to switch relay status based on fault switches

// how do we get ETC to differentiate between faults and on/off commands?


microgridIOHandler::microgridIOHandler()
{
	microgrid_init();
	thread_starter();
}

