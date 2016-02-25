#ifndef __MICROGRID_IO_HANDLER_H_
#define __MICROGRID_IO_HANDLER_H_

#include <opendnp3/outstation/ICommandHandler.h>
#include <asiodnp3/IOstation.h>

class MicroGridIOHandler final : public opendnp3::ICommandHandler
{

private:

	void Start() override{}
	void End() override{}
	
	void do_operate(const opendnp3::ControlRelayOutputBlock& command, uint8_t index);
	
	// may not be necessary with interrupt fxns
	void write_switch_value(uint_8 index, bool value);
	
	void button_interrupt(uint8_t index);
	
	void relay_interrupt(uint8_t index);
	
	void thread_starter(void);
	
	opendnp3::CommandStatus validateCROB(const opendnp3::ControlRelayOutputBlock& command, uint16_t index);
	
	
	struct status // contains the status of each switch and relay
	{
		bool fault[7]; // do we have a fault in the circuit?
		bool floor[7]; // is the circuit supposed to be active?
		bool relay[7]; // what is the actual status of the relay?
	} microgrid;
	
	public:
	
	MicroGridIOHandler();
	~MicroGridIOHandler(){};
	
	void read_measurements(asiodnp3::IOutstation* pOutstation); // reads status of each switch and relay, updates ETC
	
	// not quite sure what these fxns do. I think we may need to adapt for analog reading of battery level
	
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
