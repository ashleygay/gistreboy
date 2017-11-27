#include <instruction.hpp>
#include <processor.hpp>

/*
static uint8_t AFReadDereference(Processor *p)
{
	uint16_t address = p->F.value | (p->A.value >> 8);
	return p->_read(address);
}
*/

static uint8_t BCReadDereference(Processor *p)
{
	uint16_t address = p->C.value | (p->B.value >> 8);
	return p->_read(address);
}

static uint8_t DEReadDereference(Processor *p)
{
	uint16_t address = p->E.value | (p->D.value >> 8);
	return p->_read(address);
}

static uint8_t HLReadDereference(Processor *p)
{
	uint16_t address = p->L.value | (p->H.value >> 8);
	return p->_read(address);
}

static uint8_t check_bit(uint8_t value, uint8_t bit)
{
  return (value & (1 << bit)) != 0;
}

static uint8_t clear_bit(uint8_t value, uint8_t bit)
{
  auto clear_value = value & ~(1 << bit);
  return static_cast<uint8_t>(clear_value);
}

static uint8_t set_bit(uint8_t value, uint8_t bit)
{
  auto value_set = value | (1 << bit);
  return static_cast<uint8_t>(value_set); 
}

static uint8_t set_bit_to(uint8_t value, uint8_t bit, bool on)
{
  return on ? set_bit(value, bit) : clear_bit(value, bit);
}

static void _callPush(Processor *p)
{
	uint8_t PC_low = p->PC.value & 0xFF;
	uint8_t PC_high = p->PC.value << 8;
	p->_write(PC_low, p->SP.value--);
	p->_write(PC_high, p->SP.value--);
}

/////////////////////////////////////
/////////////// LOADS ///////////////
/////////////////////////////////////

#define LD_RegX_def(reg)\
	void LD_##reg##X::exec(Processor *p)\
	{\
	uint8_t val = boost::get<uint8_t>(this->_args[0]);\
	p->reg.value = val;\
	}

LD_RegX_def(A)
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
	{ p->A.value = HLReadDereference(p); }

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


void LD_ABC::exec(Processor *p)
{
	p->A.value = BCReadDereference(p);
}

void LD_ADE::exec(Processor *p)
{
	p->A.value = DEReadDereference(p);
}

void LD_Ann::exec(Processor *p)
{
	uint16_t address = boost::get<uint16_t>(this->_args[0]);
	p->A.value = p->_read(address);
}

void LD_BCA::exec(Processor *p)
{
	uint16_t address = p->C.value | (p->B.value >> 8);
	p->_write(p->A.value, address);
}

void LD_DEA::exec(Processor *p)
{
	uint16_t address = p->E.value | (p->D.value >> 8);
	p->_write(p->A.value, address);
}

void LD_HLA::exec(Processor *p)
{
	uint16_t address = p->L.value | (p->H.value >> 8);
	p->_write(p->A.value, address);
}

void LD_nnA::exec(Processor *p)
{
	uint16_t address = boost::get<uint16_t>(this->_args[0]);
	p->_write(p->A.value, address);
}

void LD_AC2::exec(Processor *p)
{
	uint16_t address = 0xFF00 + p->C.value;
	p->A.value = p->_read(address);
}

void LD_C2A::exec(Processor *p)
{
	uint16_t address = 0xFF00 + p->C.value;
	p->_write(p->A.value, address);
}

void LDD_AHL::exec(Processor *p)
{
	p->A.value = HLReadDereference(p);
	uint16_t HL_dec = (p->L.value | (p->H.value >> 8)) - 1;
	p->L.value = HL_dec & 0xFF;
	p->H.value = HL_dec << 8;
}

void LDD_HLA::exec(Processor *p)
{
	uint16_t HL = p->L.value | (p->H.value >> 8);
	p->_write(p->A.value, HL--); // Note: HL decremented
	p->L.value = HL & 0xFF;
	p->H.value = HL << 8;
}

void LDI_AHL::exec(Processor *p)
{
	p->A.value = HLReadDereference(p);
	uint16_t HL_inc = (p->L.value | (p->H.value >> 8)) + 1;
	p->L.value = HL_inc & 0xFF;
	p->H.value = HL_inc << 8;
}

void LDI_HLA::exec(Processor *p)
{
	uint16_t HL = p->L.value | (p->H.value >> 8);
	p->_write(p->A.value, HL++); // Note: HL incremented
	p->L.value = HL & 0xFF;
	p->H.value = HL << 8;
}

void LDH_nA::exec(Processor *p)
{
	uint16_t address = 0xFF00 + boost::get<uint8_t>(this->_args[0]);
	p->_write(p->A.value, address);
}

void LDH_An::exec(Processor *p)
{
	uint16_t address = 0xFF00 + boost::get<uint8_t>(this->_args[0]);
	p->A.value = p->_read(address);
}

void LD_BCnn::exec(Processor *p)
{
	uint16_t BC = boost::get<uint16_t>(this->_args[0]);
	p->C.value = BC & 0xFF;
	p->B.value = BC << 8;
}

void LD_DEnn::exec(Processor *p)
{
	uint16_t DE = boost::get<uint16_t>(this->_args[0]);
	p->E.value = DE & 0xFF;
	p->D.value = DE << 8;
}

void LD_HLnn::exec(Processor *p)
{
	uint16_t HL = boost::get<uint16_t>(this->_args[0]);
	p->L.value = HL & 0xFF;
	p->H.value = HL << 8;
}

void LD_SPnn::exec(Processor *p)
{
	p->SP.value = boost::get<uint16_t>(this->_args[0]);
}

void LD_nnSP::exec(Processor *p)
{
	uint16_t address = boost::get<uint16_t>(this->_args[0]);
	uint8_t SP_low = p->SP.value & 0xFF;
	uint8_t SP_high = p->SP.value << 8;

	p->_write(SP_low, address);
	p->_write(SP_high, address + 1);
}


void LD_SPHL::exec(Processor *p)
{
	p->SP.value = p->L.value | (p->H.value >> 8);
}

void LD_HLSPn::exec(Processor *p)
{
	uint8_t n = boost::get<uint8_t>(this->_args[0]);
	uint16_t HL = p->SP.value + n;
	p->L.value = HL & 0xFF;
	p->H.value = HL << 8;

	// Carry if (b1 + b1) != (b1 | b2)
	if ((HL & 0xF) != ((p->SP.value | n) & 0xF))
		p->flag.setFlag(FlagRegister::HALFCARRY);
	if (HL != (p->SP.value | n))
		p->flag.setFlag(FlagRegister::CARRY);
	p->flag.unsetFlag(FlagRegister::ZERO);
	p->flag.unsetFlag(FlagRegister::SUBTRACT);
}

/////////////////////////////////////
///////////// PUSH-POP //////////////
/////////////////////////////////////

void PUSH_BC::exec(Processor *p)
{
	p->_write(p->C.value, p->SP.value--);
	p->_write(p->B.value, p->SP.value--);
}

void PUSH_DE::exec(Processor *p)
{
	p->_write(p->E.value, p->SP.value--);
	p->_write(p->D.value, p->SP.value--);
}

void PUSH_HL::exec(Processor *p)
{
	p->_write(p->L.value, p->SP.value--);
	p->_write(p->H.value, p->SP.value--);
}

void POP_BC::exec(Processor *p)
{
	p->B.value = p->_read(p->SP.value++);
	p->C.value = p->_read(p->SP.value++);
}

void POP_DE::exec(Processor *p)
{
	p->D.value = p->_read(p->SP.value++);
	p->E.value = p->_read(p->SP.value++);
}

void POP_HL::exec(Processor *p)
{
	p->H.value = p->_read(p->SP.value++);
	p->L.value = p->_read(p->SP.value++);
}

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

void ADD_AHL::exec(Processor *p)
  {
    auto tmp = HLReadDereference(p);
    uint val = p->A.value + tmp;	
    uint8_t result = static_cast<uint8_t>(val);
    if (result == 0)
      p->flag.setFlag(FlagRegister::ZERO);
    p->flag.unsetFlag(FlagRegister::SUBTRACT);
    if (((p->A.value & 0xF) + (tmp & 0xF)) > 0xF)
      p->flag.setFlag(FlagRegister::HALFCARRY);
    if (val > 0xFF)
      p->flag.setFlag(FlagRegister::CARRY); 
    p->A.value = (result & 0xFF);
  }

void ADD_Aaddress::exec(Processor *p)
{
  auto tmp = p->_read(boost::get<uint16_t>(this->_args[0]));
  uint val = p->A.value + tmp;
  uint8_t result = static_cast<uint8_t>(val);
  if (result == 0)
    p->flag.setFlag(FlagRegister::ZERO);
  p->flag.unsetFlag(FlagRegister::SUBTRACT);
  if (((p->A.value & 0xF) + (tmp & 0xF)) > 0xF)
    p->flag.setFlag(FlagRegister::HALFCARRY);
  if (val > 0xFF)
    p->flag.setFlag(FlagRegister::CARRY);
  p->A.value = (result & 0xFF);
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

void ADC_AHL::exec(Processor *p)
{
    auto tmp = HLReadDereference(p);
    uint val = p->A.value + tmp + p->flag.getFlag(FlagRegister::CARRY);
    uint8_t result = static_cast<uint8_t>(val);
    if (result == 0)
      p->flag.setFlag(FlagRegister::ZERO);	
    p->flag.unsetFlag(FlagRegister::SUBTRACT);
    if (((p->A.value & 0xF) + (tmp & 0xF) + p->flag.getFlag(FlagRegister::CARRY)) > 0xF) 
      p->flag.setFlag(FlagRegister::HALFCARRY);
    if (val > 0xFF)
      p->flag.setFlag(FlagRegister::CARRY);
    p->A.value = (result & 0xFF);       
}

void ADC_Aaddress::exec(Processor *p)
{
  auto tmp = p->_read(boost::get<uint16_t>(this->_args[0])); 
  uint val = p->A.value + tmp + p->flag.getFlag(FlagRegister::CARRY);
  uint8_t result = static_cast<uint8_t>(val);
  if (result == 0)
    p->flag.setFlag(FlagRegister::ZERO);
  p->flag.unsetFlag(FlagRegister::SUBTRACT);
  if (((p->A.value & 0xF) + (tmp & 0xF) + p->flag.getFlag(FlagRegister::CARRY)) > 0xF)
    p->flag.setFlag(FlagRegister::HALFCARRY);
  if (val > 0xFF)
    p->flag.setFlag(FlagRegister::CARRY);
  p->A.value = (result & 0xFF);
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

void SUB_AHL::exec(Processor *p)
{
    auto tmp = HLReadDereference(p);
    uint val = p->A.value - tmp;
    uint8_t result = static_cast<uint8_t>(val);
    if (result == 0)
      p->flag.setFlag(FlagRegister::ZERO);
    p->flag.setFlag(FlagRegister::SUBTRACT);
    if (((p->A.value & 0xF) - (tmp & 0xF)) < 0)
      p->flag.setFlag(FlagRegister::HALFCARRY);
    if (p->A.value < tmp)                 
      p->flag.setFlag(FlagRegister::CARRY);
    p->A.value = (result & 0xFF);       
}


void SUB_Aaddress::exec(Processor *p)
{
  auto tmp = p->_read(boost::get<uint16_t>(this->_args[0]));    
  uint val = p->A.value - tmp;
  uint8_t result = static_cast<uint8_t>(val);
  if (result == 0)
    p->flag.setFlag(FlagRegister::ZERO);
  p->flag.setFlag(FlagRegister::SUBTRACT);
  if (((p->A.value & 0xF) - (tmp & 0xF)) < 0)
    p->flag.setFlag(FlagRegister::HALFCARRY);
  if (p->A.value < tmp)
    p->flag.setFlag(FlagRegister::CARRY);
  p->A.value = (result & 0xFF);
}

//SBC instructions

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

void SBC_AHL::exec(Processor *p)
{
  auto tmp = HLReadDereference(p);
  uint val = p->A.value - tmp - p->flag.getFlag(FlagRegister::CARRY);
  uint8_t result = static_cast<uint8_t>(val);
  if (result == 0)
    p->flag.setFlag(FlagRegister::ZERO);
  p->flag.setFlag(FlagRegister::SUBTRACT);
  if (((p->A.value & 0xF) - (tmp & 0xF) - p->flag.getFlag(FlagRegister::CARRY)) < 0) 
    p->flag.setFlag(FlagRegister::HALFCARRY);
  if (p->A.value < tmp)                 
    p->flag.setFlag(FlagRegister::CARRY);
  p->A.value = (result & 0xFF);       
}

void SBC_Aaddress::exec(Processor *p)
{
  auto tmp = p->_read(boost::get<uint16_t>(this->_args[0]));
  uint val = p->A.value - tmp - p->flag.getFlag(FlagRegister::CARRY);
  uint8_t result = static_cast<uint8_t>(val);
  if (result == 0)
    p->flag.setFlag(FlagRegister::ZERO);
  p->flag.setFlag(FlagRegister::SUBTRACT);
  if (((p->A.value & 0xF) - (tmp & 0xF) - p->flag.getFlag(FlagRegister::CARRY)) < 0)
    p->flag.setFlag(FlagRegister::HALFCARRY);
  if (p->A.value < tmp)
    p->flag.setFlag(FlagRegister::CARRY);
  p->A.value = (result & 0xFF);
}

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

void AND_AHL::exec(Processor *p)
{
  auto tmp = HLReadDereference(p);
  p->A.value &= tmp;
  if (p->A.value == 0)
    p->flag.setFlag(FlagRegister::ZERO);\
  p->flag.unsetFlag(FlagRegister::SUBTRACT);
  p->flag.setFlag(FlagRegister::HALFCARRY);
  p->flag.unsetFlag(FlagRegister::CARRY);
}

void AND_Aaddress::exec(Processor *p)
{
  auto tmp =  p->_read(boost::get<uint16_t>(this->_args[0]));
  p->A.value &= tmp;
  if (p->A.value == 0)
    p->flag.setFlag(FlagRegister::ZERO);\
  p->flag.unsetFlag(FlagRegister::SUBTRACT);
  p->flag.setFlag(FlagRegister::HALFCARRY);
  p->flag.unsetFlag(FlagRegister::CARRY);
} 

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


void OR_AHL::exec(Processor *p)
{
  auto tmp = HLReadDereference(p);
  p->A.value |= tmp;
  if (p->A.value == 0)
    p->flag.setFlag(FlagRegister::ZERO);
  p->flag.unsetFlag(FlagRegister::SUBTRACT);
  p->flag.unsetFlag(FlagRegister::HALFCARRY);
  p->flag.unsetFlag(FlagRegister::CARRY);
}

void OR_Aaddress::exec(Processor *p)
{
  auto tmp = p->_read(boost::get<uint16_t>(this->_args[0]));
  p->A.value |= tmp;
  if (p->A.value == 0)
  p->flag.setFlag(FlagRegister::ZERO);
  p->flag.unsetFlag(FlagRegister::SUBTRACT);
  p->flag.unsetFlag(FlagRegister::HALFCARRY);
  p->flag.unsetFlag(FlagRegister::CARRY);
}  
    
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


void XOR_AHL::exec(Processor *p)
{
  auto tmp = HLReadDereference(p);
  p->A.value ^= tmp;
  if (p->A.value == 0)
    p->flag.setFlag(FlagRegister::ZERO);
  p->flag.unsetFlag(FlagRegister::SUBTRACT);
  p->flag.unsetFlag(FlagRegister::HALFCARRY);
  p->flag.unsetFlag(FlagRegister::CARRY);
}

void XOR_Aaddress::exec(Processor *p)
{
  auto tmp = p->_read(boost::get<uint16_t>(this->_args[0])); 
  p->A.value ^= tmp;
  if (p->A.value == 0)
    p->flag.setFlag(FlagRegister::ZERO);
  p->flag.unsetFlag(FlagRegister::SUBTRACT);
  p->flag.unsetFlag(FlagRegister::HALFCARRY);
  p->flag.unsetFlag(FlagRegister::CARRY);
} 

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


void CP_AHL::exec(Processor *p)
{
    auto tmp = HLReadDereference(p);
    uint val = p->A.value - tmp;
    uint8_t result = static_cast<uint8_t>(val);
    if (result == 0)
      p->flag.setFlag(FlagRegister::ZERO);
    p->flag.setFlag(FlagRegister::SUBTRACT);
    if (((p->A.value & 0xF) - (tmp & 0xF)) < 0)
      p->flag.setFlag(FlagRegister::HALFCARRY);
    if (p->A.value < tmp)                 
      p->flag.setFlag(FlagRegister::CARRY);
}

void CP_Aaddress::exec(Processor *p)
{
  auto tmp = p->_read(boost::get<uint16_t>(this->_args[0]));
  uint val = p->A.value - tmp;
  uint8_t result = static_cast<uint8_t>(val);
  if (result == 0)
    p->flag.setFlag(FlagRegister::ZERO);
  p->flag.setFlag(FlagRegister::SUBTRACT);
  if (((p->A.value & 0xF) - (tmp & 0xF)) < 0)
    p->flag.setFlag(FlagRegister::HALFCARRY);
  if (p->A.value < tmp)
    p->flag.setFlag(FlagRegister::CARRY);
}  

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
//INC_RegX_def(HL)

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
//DEC_RegX_def(HL);

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
//SWAP_RegX_def(HL)

#undef SWAP_RegX_def

#define DAA_def()                  \
  void DAA::exec(Processor *p)\
  {\
    auto a = p->A.value;\
    auto tmp = p->flag.getFlag(FlagRegister::CARRY) ? 0x60 : 0x00;	\
    if (p->flag.getFlag(FlagRegister::CARRY) ||\
	(!p->flag.getFlag(FlagRegister::SUBTRACT) && ((a & 0x0F) > 9)))\
      tmp |= 0x06;\
    if (p->flag.getFlag(FlagRegister::CARRY) ||\
	(!p->flag.getFlag(FlagRegister::SUBTRACT) && (a & 0x99)))	\
      tmp |= 0x06;\
    if (p->flag.getFlag(FlagRegister::SUBTRACT))\
      a = static_cast<uint8_t>(a - tmp);\
    else\
      a = static_cast<uint8_t>(a + tmp);\
    if (((tmp << 2) & 0x100) != 0)\
      p->flag.setFlag(FlagRegister::CARRY);\
    p->flag.unsetFlag(FlagRegister::HALFCARRY);\
    if (a == 0)\
      p->flag.setFlag(FlagRegister::ZERO);\
    p->A.value = a;\
  }

DAA_def()


#define CPL_def()                  \
  void CPL::exec(Processor *p)\
  {\
    auto temp = p->A.value;\
    auto result = ~temp;\
    p->A.value = result;\
    p->flag.setFlag(FlagRegister::SUBTRACT);\
    p->flag.setFlag(FlagRegister::HALFCARRY);\
  }

CPL_def() 

#define CCF_def()                  \
  void CCF::exec(Processor *p)\
  {\
    p->flag.unsetFlag(FlagRegister::SUBTRACT);\
    p->flag.unsetFlag(FlagRegister::HALFCARRY);\
    if (p->flag.getFlag(FlagRegister::CARRY))\
      p->flag.unsetFlag(FlagRegister::CARRY);\
    else\
      p->flag.setFlag(FlagRegister::CARRY);\
  }

CCF_def() 

#define SCF_def()                  \
  void SCF::exec(Processor *p)\
  {\
    p->flag.unsetFlag(FlagRegister::SUBTRACT);\
    p->flag.unsetFlag(FlagRegister::HALFCARRY);\
    p->flag.setFlag(FlagRegister::CARRY);\
  }

SCF_def() 

/*#define BIT_BITX_def(bit, reg)		\
  void BIT_##bit##reg::exec(Processor *p)\
  {\
    p = p;\
  }

BIT_BITX_def(bit, A)
BIT_BITX_def(bit, B)
BIT_BITX_def(bit, C)
BIT_BITX_def(bit, D)
BIT_BITX_def(bit, E)
BIT_BITX_def(bit, H)
BIT_BITX_def(bit, L)  
*/

#define RRC_RegX_def(reg)                  \
  void RRC_##reg##X::exec(Processor *p)\
  {\
    auto flag_carry = check_bit(p->reg.value, 0);\
    auto truncated_bit = check_bit(p->reg.value, 0);\
    auto temp = static_cast<uint8_t>((p->reg.value >> 1) | (truncated_bit << 7));\
    p->reg.value = temp;\
    if (p->reg.value == 0)\
      p->flag.setFlag(FlagRegister::ZERO);\
    p->flag.unsetFlag(FlagRegister::SUBTRACT);\
    p->flag.unsetFlag(FlagRegister::HALFCARRY);\
    if (flag_carry)\
      p->flag.setFlag(FlagRegister::CARRY);\
    else\
      p->flag.unsetFlag(FlagRegister::CARRY);\
  }

RRC_RegX_def(A)
RRC_RegX_def(B)
RRC_RegX_def(C)
RRC_RegX_def(D)
RRC_RegX_def(E)
RRC_RegX_def(H)
RRC_RegX_def(L)
//RRC_RegX_def(HL)

#define RLC_RegX_def(reg)                  \
  void RLC_##reg##X::exec(Processor *p)\
  {\
    auto flag_carry = check_bit(p->reg.value, 7);\
    auto truncated_bit = check_bit(p->reg.value, 7);\
    auto temp = static_cast<uint8_t>((p->reg.value << 1) | truncated_bit); \
    p->reg.value = temp;\
    if (p->reg.value == 0)\
      p->flag.setFlag(FlagRegister::ZERO);\
    p->flag.unsetFlag(FlagRegister::SUBTRACT);\
    p->flag.unsetFlag(FlagRegister::HALFCARRY);\
    if (flag_carry)\
      p->flag.setFlag(FlagRegister::CARRY);\
    else\
      p->flag.unsetFlag(FlagRegister::CARRY);\
  }

RLC_RegX_def(A)
RLC_RegX_def(B)
RLC_RegX_def(C)
RLC_RegX_def(D)
RLC_RegX_def(E)
RLC_RegX_def(H)
RLC_RegX_def(L)
//RLC_RegX_def(HL) 


#define RL_RegX_def(reg)                  \
  void RL_##reg##X::exec(Processor *p)\
  {\
    auto carry = p->flag.getFlag(FlagRegister::CARRY);\
    auto flag_carry = check_bit(p->reg.value, 7);\
    if (flag_carry)\
      p->flag.setFlag(FlagRegister::CARRY);\
    else\
      p->flag.unsetFlag(FlagRegister::CARRY);\
    auto temp = static_cast<uint8_t>(p->reg.value << 1);	\
    temp |= carry;\
    if (temp == 0)\
      p->flag.setFlag(FlagRegister::ZERO);\
    p->flag.unsetFlag(FlagRegister::SUBTRACT);\
    p->flag.unsetFlag(FlagRegister::HALFCARRY);\
    p->reg.value = temp;\
  }

RL_RegX_def(A)
RL_RegX_def(B)
RL_RegX_def(C)
RL_RegX_def(D)
RL_RegX_def(E)
RL_RegX_def(H)
RL_RegX_def(L)
//RL_RegX_def(HL)

#define RR_RegX_def(reg)                  \
  void RR_##reg##X::exec(Processor *p)\
  {\
   auto carry = p->flag.getFlag(FlagRegister::CARRY);\
   auto flag_carry = check_bit(p->reg.value, 0);\
   if (flag_carry)\
     p->flag.setFlag(FlagRegister::CARRY);\
   else\
     p->flag.unsetFlag(FlagRegister::CARRY);\
   auto temp = static_cast<uint8_t>(p->reg.value >> 1);	\
   temp |= carry;\
   if (temp == 0)\
     p->flag.setFlag(FlagRegister::ZERO);\
   p->flag.unsetFlag(FlagRegister::SUBTRACT);\
   p->flag.unsetFlag(FlagRegister::HALFCARRY);\
   p->reg.value = temp;\
}

RR_RegX_def(A)
RR_RegX_def(B)
RR_RegX_def(C)
RR_RegX_def(D)
RR_RegX_def(E)
RR_RegX_def(H)
RR_RegX_def(L)
//RR_RegX_def(HL) 

#define SLA_RegX_def(reg)                  \
  void SLA_##reg##X::exec(Processor *p)\
  {\
    auto flag_carry = check_bit(p->reg.value, 7);\
    if (flag_carry)\
      p->flag.setFlag(FlagRegister::CARRY);\
    else\
      p->flag.unsetFlag(FlagRegister::CARRY);\
    auto temp = static_cast<uint8_t>(p->reg.value << 1);	\
    if (temp == 0)\
      p->flag.setFlag(FlagRegister::ZERO);\
    p->flag.unsetFlag(FlagRegister::SUBTRACT);\
    p->flag.unsetFlag(FlagRegister::HALFCARRY);\
    p->reg.value = temp;\
  }

SLA_RegX_def(A)
SLA_RegX_def(B)
SLA_RegX_def(C)
SLA_RegX_def(D)
SLA_RegX_def(E)
SLA_RegX_def(H)
SLA_RegX_def(L)
//SLA_RegX_def(HL)

#define SRA_RegX_def(reg)                  \
  void SRA_##reg##X::exec(Processor *p)\
  {\
    auto bit_carry = check_bit(p->reg.value, 0);\
    auto top_bit = check_bit(p->reg.value, 7);\
    auto temp = static_cast<uint8_t>(p->reg.value >> 1);        \
    temp = set_bit_to(temp, 7, top_bit);				\
    if (temp == 0)\
      p->flag.setFlag(FlagRegister::ZERO);\
    if (bit_carry)\
      p->flag.setFlag(FlagRegister::CARRY);\
    else\
      p->flag.unsetFlag(FlagRegister::CARRY);\
    p->flag.unsetFlag(FlagRegister::SUBTRACT);\
    p->flag.unsetFlag(FlagRegister::HALFCARRY);\
    p->reg.value = temp;\
  }

SRA_RegX_def(A)
SRA_RegX_def(B)
SRA_RegX_def(C)
SRA_RegX_def(D)
SRA_RegX_def(E)
SRA_RegX_def(H)
SRA_RegX_def(L)
//SRA_RegX_def(HL)

#define SRL_RegX_def(reg)                  \
  void SRL_##reg##X::exec(Processor *p)\
  {\
    bool leastbitset = check_bit(p->reg.value, 0);\
    auto temp = static_cast<uint8_t>(p->reg.value >> 1);        \
    if (temp == 0)\
      p->flag.setFlag(FlagRegister::ZERO);\
    if (leastbitset)\
      p->flag.setFlag(FlagRegister::CARRY);\
    else\
      p->flag.unsetFlag(FlagRegister::CARRY);\
    p->flag.unsetFlag(FlagRegister::SUBTRACT);\
    p->flag.unsetFlag(FlagRegister::HALFCARRY);\
    p->reg.value = temp;\
  }

SRL_RegX_def(A)
SRL_RegX_def(B)
SRL_RegX_def(C)
SRL_RegX_def(D)
SRL_RegX_def(E)
SRL_RegX_def(H)
SRL_RegX_def(L)
//SRL_RegX_def(HL) 

/////////////////////////////////////
/////////////// JUMPS ///////////////
/////////////////////////////////////

void JP::exec(Processor *p)
{
	p->PC.value = boost::get<uint16_t>(this->_args[0]);
}

void JPNZ::exec(Processor *p)
{
	if ( !p->flag.getFlag(FlagRegister::ZERO))
		p->PC.value = boost::get<uint16_t>(this->_args[0]);
}

void JPZ::exec(Processor *p)
{
	if ( p->flag.getFlag(FlagRegister::ZERO))
		p->PC.value = boost::get<uint16_t>(this->_args[0]);
}

void JPNC::exec(Processor *p)
{
	if ( !p->flag.getFlag(FlagRegister::CARRY))
		p->PC.value = boost::get<uint16_t>(this->_args[0]);
}

void JPC::exec(Processor *p)
{
	if ( p->flag.getFlag(FlagRegister::CARRY))
		p->PC.value = boost::get<uint16_t>(this->_args[0]);
}

void JPHL::exec(Processor *p)
{
	p->PC.value = p->L.value | (p->H.value >> 8);
}

void JR::exec(Processor *p)
{
	p->PC.value += (int8_t) boost::get<uint8_t>(this->_args[0]);
}

void JRNZ::exec(Processor *p)
{
	if ( !p->flag.getFlag(FlagRegister::ZERO))
		p->PC.value += (int8_t) boost::get<uint8_t>(this->_args[0]);
}

void JRZ::exec(Processor *p)
{
	if ( p->flag.getFlag(FlagRegister::ZERO))
		p->PC.value += (int8_t) boost::get<uint8_t>(this->_args[0]);
}

void JRNC::exec(Processor *p)
{
	if ( !p->flag.getFlag(FlagRegister::CARRY))
		p->PC.value += (int8_t) boost::get<uint8_t>(this->_args[0]);
}

void JRC::exec(Processor *p)
{
	if ( p->flag.getFlag(FlagRegister::CARRY))
		p->PC.value = (int8_t) boost::get<uint8_t>(this->_args[0]);
}

/////////////////////////////////////
/////////////// CALLS ///////////////
/////////////////////////////////////

void CALL::exec(Processor *p)
{
	_callPush(p);
}

void CALLNZ::exec(Processor *p)
{
	if ( !p->flag.getFlag(FlagRegister::ZERO)) {
		_callPush(p);
		p->PC.value = boost::get<uint16_t>(this->_args[0]);
	}
}

void CALLZ::exec(Processor *p)
{
	if ( p->flag.getFlag(FlagRegister::ZERO)) {
		_callPush(p);
		p->PC.value = boost::get<uint16_t>(this->_args[0]);
	}
}

void CALLNC::exec(Processor *p)
{
	if ( !p->flag.getFlag(FlagRegister::CARRY)) {
		_callPush(p);
		p->PC.value = boost::get<uint16_t>(this->_args[0]);
	}
}

void CALLC::exec(Processor *p)
{
	if ( p->flag.getFlag(FlagRegister::CARRY)) {
		_callPush(p);
		p->PC.value = boost::get<uint16_t>(this->_args[0]);
	}
}
