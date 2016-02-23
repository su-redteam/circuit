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

#define FAULTMASTER 0
#define FAULT1 1
#define FAULT2 2
#define FAULT3 3
#define FAULT4 4
#define FAULT5 5
#define FAULT6 6
 
#define BUTTONMASTER 7
#define BUTTON1 8
#define BUTTON2 9
#define BUTTON3 10
#define BUTTON4 11
#define BUTTON5 12
#define BUTTON6 13

#define RELAYMASTER 14
#define RELAY1 15
#define RELAY2 16
#define RELAY3 17
#define RELAY4 18
#define RELAY5 19
#define RELAY6 20


void MicroGridIOHandler::DoOperate(const ControlRelayOutputBlock& command, uint_8 index)
{
	uint_8 value = (command.functionCode == ControlCode::LATCH_ON) ? 1 : 0;
	writeSwitchValue(index, value);
}

CommandStatus MicroGridIOHandler::ValidateCROB(const ControlRelayOutputBlock& command, uint_16 index)
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

void writeSwitchValue(uint_8 index, bool value)
void buttonInterrupt(int num)
{
	this->status.floor[num] = !this->status.floor[num]
}


// sample code to be used in building ISR for button presses

//  if ( wiringPiISR (BUTTON_PIN, INT_EDGE_FALLING, &myInterrupt) < 0 ) {
//      fprintf (stderr, "Unable to setup ISR: %s\n", strerror (errno));
//      return 1;
//  }
