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

#define LD_XHL_def(reg)\
	void LD_##reg##HL::exec(Processor *p)\
	{\
		uint16_t address = p->L.value | (p->H.value >> 8);\
		uint8_t value = p->_read(address);\
		p->A.value = value;\
	}

#define LD_HLX_def(reg)\
	void LD_HL##reg::exec(Processor *p)\
	{\
		uint16_t address = p->L.value | (p->H.value >> 8);\
		uint8_t value = p->A.value;\
		p->_write(value, address);\
	}

LD_XY_def(A,A)
LD_XY_def(A,B)
LD_XY_def(A,C)
LD_XY_def(A,D)
LD_XY_def(A,E)
LD_XY_def(A,H)
LD_XY_def(A,L)
LD_XHL_def(A)
LD_XY_def(B,A)
LD_XY_def(B,B)
LD_XY_def(B,C)
LD_XY_def(B,D)
LD_XY_def(B,E)
LD_XY_def(B,H)
LD_XY_def(B,L)
LD_XHL_def(B)
LD_XY_def(C,A)
LD_XY_def(C,B)
LD_XY_def(C,C)
LD_XY_def(C,D)
LD_XY_def(C,E)
LD_XY_def(C,H)
LD_XY_def(C,L)
LD_XHL_def(C)
LD_XY_def(D,A)
LD_XY_def(D,B)
LD_XY_def(D,C)
LD_XY_def(D,D)
LD_XY_def(D,E)
LD_XY_def(D,H)
LD_XY_def(D,L)
LD_XHL_def(D)
LD_XY_def(E,A)
LD_XY_def(E,B)
LD_XY_def(E,C)
LD_XY_def(E,D)
LD_XY_def(E,E)
LD_XY_def(E,H)
LD_XY_def(E,L)
LD_XHL_def(E)
LD_XY_def(H,A)
LD_XY_def(H,B)
LD_XY_def(H,C)
LD_XY_def(H,D)
LD_XY_def(H,E)
LD_XY_def(H,H)
LD_XY_def(H,L)
LD_XHL_def(H)
LD_XY_def(L,A)
LD_XY_def(L,B)
LD_XY_def(L,C)
LD_XY_def(L,D)
LD_XY_def(L,E)
LD_XY_def(L,H)
LD_XY_def(L,L)
LD_XHL_def(L)
LD_HLX_def(B)
LD_HLX_def(C)
LD_HLX_def(D)
LD_HLX_def(E)
LD_HLX_def(H)
LD_HLX_def(L)

void LD_HLn::exec(Processor *p)
{
	uint16_t address = p->L.value | (p->H.value >> 8);
	uint8_t value = boost::get<uint8_t>(this->_args[0]);
	p->_write(value, address);
}

#undef LD_XY_def
#undef LD_XHL_def
#undef LD_HLX_def



void NOP::exec(Processor *p)
{
	(void)p;
}



//ADD instructions


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

#undef CP_RegX_def  

// INC instructions

#define INC_RegX_def(reg)                  \
  void INC_##reg##X::exec(Processor *p)\
  {\
    p->reg.value += 1;\
    if (p->reg.value == 0)\
      p->flag.setFlag(FlagRegister::ZERO);\
    p->flag.unsetFlag(FlagRegister::SUBTRACT);\
    if ((p->reg.value & 0xF) == 0x00) \
      p->flag.setFlag(FlagRegister::HALFCARRY);\
  }

INC_RegX_def(A)
INC_RegX_def(B)
INC_RegX_def(C)
INC_RegX_def(D)
INC_RegX_def(E)
INC_RegX_def(H)
INC_RegX_def(L)
// TODO INC_RegX_def(HL);

#undef DEC_RegX_def 

// DEC instructions

#define DEC_RegX_def(reg)                  \
  void DEC_##reg##X::exec(Processor *p)\
  {\
    p->reg.value -= 1;\
    if (p->reg.value == 0)\
      p->flag.setFlag(FlagRegister::ZERO);\
    p->flag.setFlag(FlagRegister::SUBTRACT);\
    if ((p->reg.value & 0xF) == 0x0F) \
      p->flag.setFlag(FlagRegister::HALFCARRY);\
  }

DEC_RegX_def(A)
DEC_RegX_def(B)
DEC_RegX_def(C)
DEC_RegX_def(D)
DEC_RegX_def(E)
DEC_RegX_def(H)
DEC_RegX_def(L)
// TODO DEC_RegX_def(HL);

#undef DEC_RegX_def

// SWAP instructions

#define SWAP_RegX_def(reg)                  \
  void SWAP_##reg##X::exec(Processor *p)\
  {\
    auto a = p->reg.value >> 4;			\
    auto b = p->reg.value << 4;\
    auto temp = a | b;\
    p->reg.value = temp;\
    if (p->reg.value == 0)\
      p->flag.setFlag(FlagRegister::ZERO);\
    p->flag.unsetFlag(FlagRegister::SUBTRACT);\
    p->flag.unsetFlag(FlagRegister::HALFCARRY);\
    p->flag.unsetFlag(FlagRegister::CARRY);\
  }

SWAP_RegX_def(A)
SWAP_RegX_def(B)
SWAP_RegX_def(C)
SWAP_RegX_def(D)
SWAP_RegX_def(E)
SWAP_RegX_def(H)
SWAP_RegX_def(L)
// TODO SWAP_RegX_def(HL);

#undef SWAP_RegX_def
