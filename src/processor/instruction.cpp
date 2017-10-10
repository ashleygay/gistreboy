#include <instruction.hpp>
#include <processor.hpp>

void LD_BX::exec(Processor *p)
{
	uint8_t val = boost::get<uint8_t>(this->_args[0]);
	DEBUG_PRINT << "Got value : " << val << std::endl;
	p->B.value = val;
}

void NOP::exec(Processor *p)
{
	(void)p;
}
