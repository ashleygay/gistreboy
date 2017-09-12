#include <instruction.hpp>

LD_BX::LD_BX(InstructionArgs args)
{
	this->args = args;
}

void LD_BX::exec()
{
	Processor& proc = Processor::getInstance();
	proc.registerB.value = boost::get<uint8_t>(this->args[0]);
}
