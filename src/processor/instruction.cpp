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
	{ p->reg1.value = p->reg2.value;}

LD_XY_def(A,A)
LD_XY_def(A,B)
LD_XY_def(A,C)
LD_XY_def(A,D)
LD_XY_def(A,E)
LD_XY_def(A,H)
LD_XY_def(A,L)
// TODO : A, HL
LD_XY_def(B,A)
LD_XY_def(B,B)
LD_XY_def(B,C)
LD_XY_def(B,D)
LD_XY_def(B,E)
LD_XY_def(B,H)
LD_XY_def(B,L)
// TODO : B, HL
LD_XY_def(C,A)
LD_XY_def(C,B)
LD_XY_def(C,C)
LD_XY_def(C,D)
LD_XY_def(C,E)
LD_XY_def(C,H)
LD_XY_def(C,L)
// TODO : C, HL
LD_XY_def(D,A)
LD_XY_def(D,B)
LD_XY_def(D,C)
LD_XY_def(D,D)
LD_XY_def(D,E)
LD_XY_def(D,H)
LD_XY_def(D,L)
// TODO : D, HL
LD_XY_def(E,A)
LD_XY_def(E,B)
LD_XY_def(E,C)
LD_XY_def(E,D)
LD_XY_def(E,E)
LD_XY_def(E,H)
LD_XY_def(E,L)
// TODO : E, HL
LD_XY_def(H,A)
LD_XY_def(H,B)
LD_XY_def(H,C)
LD_XY_def(H,D)
LD_XY_def(H,E)
LD_XY_def(H,H)
LD_XY_def(H,L)
// TODO : H, HL
LD_XY_def(L,A)
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


//ADD instructions

#undef LD_XY_def

#define ADD_XY_def(reg1, reg2)\
  void ADD_##reg1##reg2::exec(Processor *p)\
  {\
  	uint val = p->reg1.value + p->reg2.value;\
	uint8_t result = static_cast<uint8_t>(val);\
	if (result == 0)\
	  p->flag.setFlag(FlagRegister::ZERO);\
	p->flag.unsetFlag(FlagRegister::SUBTRACT);\
	if (((p->reg1.value & 0xF) + (p->reg2.value & 0xF)) > 0xF)\
	  p->flag.setFlag(FlagRegister::HALFCARRY);\
	if (val > 0xFF)\
	  p->flag.setFlag(FlagRegister::CARRY);	\
	p->reg1.value = (result & 0xFF);\
}

ADD_XY_def(A, A)
ADD_XY_def(A, B)
ADD_XY_def(A, C)
ADD_XY_def(A, D)
ADD_XY_def(A, E)
ADD_XY_def(A, H)
ADD_XY_def(A, L)
// TODO ADD_XY_def(A, HL); 

#undef ADD_XY_def

void ADD_AADDRESS::exec(Processor *p)
{
  p = p;
  /*auto mem = p._read(this->args[0]);*/
}    

//ADC instructions

#define ADC_XY_def(reg1, reg2)			\
  void ADC_##reg1##reg2::exec(Processor *p)\
  {\
    uint val = p->reg1.value + p->reg2.value + p->flag.getFlag(FlagRegister::CARRY);\
    uint8_t result = static_cast<uint8_t>(val);\
    if (result == 0)\
      p->flag.setFlag(FlagRegister::ZERO);\
    p->flag.unsetFlag(FlagRegister::SUBTRACT);\
    if (((p->reg1.value & 0xF) + (p->reg2.value & 0xF) + p->flag.getFlag(FlagRegister::CARRY)) > 0xF) \
      p->flag.setFlag(FlagRegister::HALFCARRY);\
    if (val > 0xFF)\
      p->flag.setFlag(FlagRegister::CARRY);\
    p->reg1.value = (result & 0xFF);	   \
  }

ADC_XY_def(A, A)
ADC_XY_def(A, B)
ADC_XY_def(A, C)
ADC_XY_def(A, D)
ADC_XY_def(A, E)
ADC_XY_def(A, H)
ADC_XY_def(A, L)
// TODO ADC_XY_def(A, HL);

#undef ADC_XY_def        

void ADC_AADDRESS::exec(Processor *p)
{
  p = p;
  /*auto mem = p._read(this->args[0]);*/
} 

//SUB instructions

#define SUB_XY_def(reg1, reg2)                  \
  void SUB_##reg1##reg2::exec(Processor *p)\
  {\
    uint val = p->reg1.value - p->reg2.value;\
    uint8_t result = static_cast<uint8_t>(val);\
    if (result == 0)\
      p->flag.setFlag(FlagRegister::ZERO);\
    p->flag.setFlag(FlagRegister::SUBTRACT);\
    if (((p->reg1.value & 0xF) - (p->reg2.value & 0xF)) < 0) \
      p->flag.setFlag(FlagRegister::HALFCARRY);\
    if (p->reg1.value < p->reg2.value)		       \
      p->flag.setFlag(FlagRegister::CARRY);\
    p->reg1.value = (result & 0xFF);       \
  }

SUB_XY_def(A, A)
SUB_XY_def(A, B)
SUB_XY_def(A, C)
SUB_XY_def(A, D)
SUB_XY_def(A, E)
SUB_XY_def(A, H)
SUB_XY_def(A, L)
// TODO SUB_XY_def(A, HL);

#undef SUB_XY_def

void SUB_AADDRESS::exec(Processor *p)
{
  p = p;
  /*auto mem = p._read(this->args[0]);*/
}          

//SUB instructions

#define SBC_XY_def(reg1, reg2)                  \
  void SBC_##reg1##reg2::exec(Processor *p)\
  {\
    uint val = p->reg1.value - p->reg2.value - p->flag.getFlag(FlagRegister::CARRY); \
    uint8_t result = static_cast<uint8_t>(val);\
    if (result == 0)\
      p->flag.setFlag(FlagRegister::ZERO);\
    p->flag.setFlag(FlagRegister::SUBTRACT);\
    if (((p->reg1.value & 0xF) - (p->reg2.value & 0xF) - p->flag.getFlag(FlagRegister::CARRY)) < 0) \
      p->flag.setFlag(FlagRegister::HALFCARRY);\
    if (p->reg1.value < p->reg2.value)                 \
      p->flag.setFlag(FlagRegister::CARRY);\
    p->reg1.value = (result & 0xFF);       \
  }

SBC_XY_def(A, A)
SBC_XY_def(A, B)
SBC_XY_def(A, C)
SBC_XY_def(A, D)
SBC_XY_def(A, E)
SBC_XY_def(A, H)
SBC_XY_def(A, L)
// TODO SBC_XY_def(A, HL);

#undef SBC_XY_def

//AND instructions

#define AND_XY_def(reg1, reg2)                  \
  void AND_##reg1##reg2::exec(Processor *p)\
  {\
    p->reg1.value &= p->reg2.value; \
    if (p->reg1.value == 0)\
      p->flag.setFlag(FlagRegister::ZERO);\
    p->flag.unsetFlag(FlagRegister::SUBTRACT);\
    p->flag.setFlag(FlagRegister::HALFCARRY);\
    p->flag.unsetFlag(FlagRegister::CARRY);\
  }

AND_XY_def(A, A)
AND_XY_def(A, B)
AND_XY_def(A, C)
AND_XY_def(A, D)
AND_XY_def(A, E)
AND_XY_def(A, H)
AND_XY_def(A, L)
// TODO AND_XY_def(A, HL);

#undef AND_XY_def  


//OR instructions

#define OR_XY_def(reg1, reg2)                  \
  void OR_##reg1##reg2::exec(Processor *p)\
  {\
    p->reg1.value |= p->reg2.value; \
    if (p->reg1.value == 0)\
      p->flag.setFlag(FlagRegister::ZERO);\
    p->flag.unsetFlag(FlagRegister::SUBTRACT);\
    p->flag.unsetFlag(FlagRegister::HALFCARRY);\
    p->flag.unsetFlag(FlagRegister::CARRY);\
  }

OR_XY_def(A, A)
OR_XY_def(A, B)
OR_XY_def(A, C)
OR_XY_def(A, D)
OR_XY_def(A, E)
OR_XY_def(A, H)
OR_XY_def(A, L)
// TODO OR_XY_def(A, HL);

#undef OR_XY_def

//XOR instructions

#define XOR_XY_def(reg1, reg2)                  \
  void XOR_##reg1##reg2::exec(Processor *p)\
  {\
    p->reg1.value ^= p->reg2.value; \
    if (p->reg1.value == 0)\
      p->flag.setFlag(FlagRegister::ZERO);\
    p->flag.unsetFlag(FlagRegister::SUBTRACT);\
    p->flag.unsetFlag(FlagRegister::HALFCARRY);\
    p->flag.unsetFlag(FlagRegister::CARRY);\
  }

XOR_XY_def(A, A)
XOR_XY_def(A, B)
XOR_XY_def(A, C)
XOR_XY_def(A, D)
XOR_XY_def(A, E)
XOR_XY_def(A, H)
XOR_XY_def(A, L)
// TODO XOR_XY_def(A, HL);

#undef XOR_XY_def  


//CP instructions

#define CP_XY_def(reg1, reg2)                  \
  void CP_##reg1##reg2::exec(Processor *p)\
  {\
    uint val = p->reg1.value - p->reg2.value;\
    uint8_t result = static_cast<uint8_t>(val);\
    if (result == 0)\
      p->flag.setFlag(FlagRegister::ZERO);\
    p->flag.setFlag(FlagRegister::SUBTRACT);\
    if (((p->reg1.value & 0xF) - (p->reg2.value & 0xF)) < 0) \
      p->flag.setFlag(FlagRegister::HALFCARRY);\
    if (p->reg1.value < p->reg2.value)                 \
      p->flag.setFlag(FlagRegister::CARRY);\  
  }

CP_XY_def(A, A)
CP_XY_def(A, B)
CP_XY_def(A, C)
CP_XY_def(A, D)
CP_XY_def(A, E)
CP_XY_def(A, H)
CP_XY_def(A, L)
// TODO CP_XY_def(A, HL);

#undef CP_XY_def  
