#include <instruction.hpp>

LD_BX::LD_BX(InstructionArgs args)
{
	this->args = args;
}

void LD_BX::exec()
{
	Processor& proc = Processor::getInstance();
	uint8_t val = boost::get<uint8_t>(this->args[0]);
	DEBUG_PRINT << "Got value : " << val << std::endl;
	proc.registerB.value = boost::get<uint8_t>(this->args[0]);
}
