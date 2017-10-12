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


void ADD_AA::exec(Processor *p)
{
  	uint8_t val = boost::get<uint8_t>(this->_args[1]);
  	DEBUG_PRINT << "Got value : " << val << std::endl;
  	p->A.value = p->A.value = val;
	if (p->A.value == 0)
	  p->flag.setFlag(ZERO);
	p->flag.unsetFlag(SUBTRACT);

	/// il manque le set du flag C et H
} 
