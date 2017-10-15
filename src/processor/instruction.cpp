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

#define LD_XY_def(reg1, reg2)\
	void LD_##reg1##reg2::exec(Processor *p)\
	{\ p->reg.value = p->reg2.value;\ }

LD_XY_def(A,A)
LD_XY_def(A,B)
LD_XY_def(A,C)
LD_XY_def(A,D)
LD_XY_def(A,E)
LD_XY_def(A,H)
LD_XY_def(A,L)
// TODO : A, HL
LD_XY_def(B,B)
LD_XY_def(B,C)
LD_XY_def(B,D)
LD_XY_def(B,E)
LD_XY_def(B,H)
LD_XY_def(B,L)
// TODO : B, HL
LD_XY_def(C,B)
LD_XY_def(C,C)
LD_XY_def(C,D)
LD_XY_def(C,E)
LD_XY_def(C,H)
LD_XY_def(C,L)
// TODO : C, HL
LD_XY_def(D,B)
LD_XY_def(D,C)
LD_XY_def(D,D)
LD_XY_def(D,E)
LD_XY_def(D,H)
LD_XY_def(D,L)
// TODO : D, HL
LD_XY_def(E,B)
LD_XY_def(E,C)
LD_XY_def(E,D)
LD_XY_def(E,E)
LD_XY_def(E,H)
LD_XY_def(E,L)
// TODO : E, HL
LD_XY_def(H,B)
LD_XY_def(H,C)
LD_XY_def(H,D)
LD_XY_def(H,E)
LD_XY_def(H,H)
LD_XY_def(H,L)
// TODO : H, HL
LD_XY_def(L,B)
LD_XY_def(L,C)
LD_XY_def(L,D)
LD_XY_def(L,E)
LD_XY_def(L,H)
LD_XY_def(L,L)
// TODO : L, HL
// TODO : HL, B
// TODO : HL, C
// TODO : HL, D
// TODO : HL, E
// TODO : HL, H
// TODO : HL, L
// TODO : HL, n



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
