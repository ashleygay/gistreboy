#include <instruction.hpp>
#include <processor.hpp>

void LD_BX::exec(Processor *p)
{
	uint8_t val = boost::get<uint8_t>(this->_args[0]);
	DEBUG_PRINT << "Got value : " << val << std::endl;
	p->B.value = val;
}
#define LD_RegX_def(reg)\
	void LD_##reg##X::exec(Processor *p)\
	{\
	uint8_t val = boost::get<uint8_t>(this->_args[0]);\
	DEBUG_PRINT << "Got value : " << val << std::endl;\
	p->reg.value = val;\
	}


#undef LD_RegX_def


void NOP::exec(Processor *p)
{
	(void)p;
}


void ADD_AA::exec(Processor *p)
{
  	uint8_t val = boost::get<uint8_t>(this->_args[1]);
  	DEBUG_PRINT << "Got value : " << val << std::endl;
  	p->A.value = val;
	if (p->A.value == 0)
	  p->flag.setFlag(FlagRegister::ZERO);
	p->flag.unsetFlag(FlagRegister::SUBTRACT);

	/// il manque le set du flag C et H
}
