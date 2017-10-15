#include <instruction.hpp>
#include <processor.hpp>

#define LD_RegX_def(reg)\
	void LD_##reg##X::exec(Processor *p)\
	{\
	uint8_t val = boost::get<uint8_t>(this->_args[0]);\
	DEBUG_PRINT << "Got value : " << val << std::endl;\
	p->reg.value = val;\
	}

LD_RegX_def(B)
LD_RegX_def(C)
LD_RegX_def(D)
LD_RegX_def(E)
LD_RegX_def(H)
LD_RegX_def(L)

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
