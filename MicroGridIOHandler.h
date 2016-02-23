#ifndef __MICROGRID_IO_HANDLER_H_
#define __MICROGRID_IO_HANDLER_H_

#include <opendnp3/outstation/ICommandHandler.h>
#include <asiodnp3/IOstation.h>

class MicroGridIOHandler final : public opendnp3::ICommandHandler
{

private:

	void Start() override{}
	void End() override{}
	
	void DoOperate(const opendnp3::ControlRelayOutputBlock& command, uint8_t index);
	
	void writeSwitchValue(uint_8 index, bool value);
	
	opendnp3::CommandStatus ValidateCROB(const opendnp3::ControlRelayOutputBlock& command, uint16_t index);
	
	
	struct status // contains the status of each switch and relay
	{
		bool fault[7];
		bool floor[7];
		bool relay[7];
	}
	public:
	
	MicroGridIOHandler();
	~MicroGridIOHandler();
	
	void ReadMeasurements(asiodnp3::IOutstation* pOutstation); // reads status of each switch and relay, updates ETC
	void buttonInterrupt(int num); //ISR for button presses

	opendnp3::CommandStatus Select(const opendnp3::ControlRelayOutputBlock& command, uint16_t index);
	opendnp3::CommandStatus Operate(const opendnp3::ControlRelayOutputBlock& command, uint16_t index);
	
	opendnp3::CommandStatus Select(const opendnp3::AnalogOutputInt16& command, uint16_t index) 
		override {return opendnp3::CommandStatus::NOT_SUPPORTED; }
	opendnp3::CommandStatus Operate(const opendnp3::AnalogOutputInt16& command, uint16_t index) 
		override {return opendnp3::CommandStatus::NOT_SUPPORTED; }		
		
	opendnp3::CommandStatus Select(const opendnp3::AnalogOutputInt32& command, uint16_t index) 
		override {return opendnp3::CommandStatus::NOT_SUPPORTED; }
	opendnp3::CommandStatus Operate(const opendnp3::AnalogOutputInt32& command, uint16_t index) 
		override {return opendnp3::CommandStatus::NOT_SUPPORTED; }		
		
	opendnp3::CommandStatus Select(const opendnp3::AnalogOutputFloat16& command, uint16_t index) 
		override {return opendnp3::CommandStatus::NOT_SUPPORTED; }
	opendnp3::CommandStatus Operate(const opendnp3::AnalogOutputFloat16& command, uint16_t index) 
		override {return opendnp3::CommandStatus::NOT_SUPPORTED; }		
		
	opendnp3::CommandStatus Select(const opendnp3::AnalogOutputDouble64& command, uint16_t index) 
		override {return opendnp3::CommandStatus::NOT_SUPPORTED; }
	opendnp3::CommandStatus Operate(const opendnp3::AnalogOutputDouble64& command, uint16_t index) 
		override {return opendnp3::CommandStatus::NOT_SUPPORTED; }		
		
};

#endif
