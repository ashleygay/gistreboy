#include <instruction.hpp>
#include <processor.hpp>

void LD_BX::exec()
{
	Processor& proc = Processor::getInstance();
	uint8_t val = boost::get<uint8_t>(this->_args[0]);
	DEBUG_PRINT << "Got value : " << val << std::endl;
	proc.registerB.value = val;
}
