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
  	uint8_t val = p->A.value * 2;
	if ((val & 0xFF) == 0)
	  p->flag.setFlag(ZERO);			         /// IF result = 0 so set Z 
	p->flag.unsetFlag(FlagRegister::SUBTRACT);               /// reset N
	if (((p->A.value & 0xF) + (p->A.value & 0xF)) > 0xF)     /// Set if carry from bit 3
	  p->flag.setFlag(HALFCARRY);
	if (val > 0xFF)                                          /// Set if carry from bit 7
	  p->flag.setFlag(CARRY);

	p->A.value = (val & 0xFF);
}
