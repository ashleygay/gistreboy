#include <instruction.hpp>
#include <processor.hpp>

static uint8_t BCReadDereference(Processor *p)
{
	uint16_t address = make_word(p->C.value, p->B.value);
	return p->_read(address);
}

static uint8_t DEReadDereference(Processor *p)
{
	uint16_t address = make_word(p->E.value, p->D.value);
	return p->_read(address);
}

static uint8_t HLReadDereference(Processor *p)
{
	uint16_t address = make_word(p->L.value, p->H.value);
	return p->_read(address);
}

static void HLWriteDereference(Processor *p, uint8_t value)
{
	uint16_t address = make_word(p->L.value, p->H.value);
	p->_write(value, address);
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
	p->push_word(p->PC.value);
}

static void _return(Processor *p)
{
	p->PC.value = p->pop_word();
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
		uint16_t address = make_word(p->L.value, p->H.value);\
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
	uint16_t address = make_word(p->L.value, p->H.value);
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
	uint16_t address = make_word(p->C.value, p->B.value);
	p->_write(p->A.value, address);
}

void LD_DEA::exec(Processor *p)
{
	uint16_t address = make_word(p->E.value, p->D.value);
	p->_write(p->A.value, address);
}

void LD_HLA::exec(Processor *p)
{
	uint16_t address = make_word(p->L.value, p->H.value);
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
	uint16_t HL_dec = make_word(p->L.value, p->H.value) - 1;
	p->L.value = get_low(HL_dec);
	p->H.value = get_high(HL_dec);
}

void LDD_HLA::exec(Processor *p)
{
	uint16_t HL = make_word(p->L.value, p->H.value);
	p->_write(p->A.value, HL--); // Note: HL decremented
	p->L.value = get_low(HL);
	p->H.value = get_high(HL);
}

void LDI_AHL::exec(Processor *p)
{
	p->A.value = HLReadDereference(p);
	uint16_t HL_inc = make_word(p->L.value, p->H.value) + 1;
	p->L.value = get_low(HL_inc);
	p->H.value = get_high(HL_inc);
}

void LDI_HLA::exec(Processor *p)
{
	uint16_t HL = make_word(p->L.value, p->H.value);
	p->_write(p->A.value, HL++); // Note: HL incremented
	p->L.value = get_low(HL);
	p->H.value = get_high(HL);
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
	p->C.value = get_low(BC);
	p->B.value = get_high(BC);
}

void LD_DEnn::exec(Processor *p)
{
	uint16_t DE = boost::get<uint16_t>(this->_args[0]);
	p->E.value = get_low(DE);
	p->D.value = get_high(DE);
}

void LD_HLnn::exec(Processor *p)
{
	uint16_t HL = boost::get<uint16_t>(this->_args[0]);
	p->L.value = get_low(HL);
	p->H.value = get_high(HL);
}

void LD_SPnn::exec(Processor *p)
{
	p->SP.value = boost::get<uint16_t>(this->_args[0]);
}

void LD_nnSP::exec(Processor *p)
{
	uint16_t address = boost::get<uint16_t>(this->_args[0]);
	uint8_t SP_low = get_low(p->SP.value);
	uint8_t SP_high = get_low(p->SP.value);

	p->_write(SP_low, address);
	p->_write(SP_high, address + 1);
}


void LD_SPHL::exec(Processor *p)
{
	p->SP.value = make_word(p->L.value, p->H.value);
}

void LD_HLSPn::exec(Processor *p)
{
	uint8_t n = boost::get<uint8_t>(this->_args[0]);
	uint16_t HL = p->SP.value + n;
	p->L.value = get_low(HL);
	p->H.value = get_high(HL);

	p->flag.unsetFlag(FlagRegister::HALFCARRY);
	p->flag.unsetFlag(FlagRegister::CARRY);
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
	p->flag.unsetFlag(FlagRegister::ZERO);\
	p->flag.unsetFlag(FlagRegister::HALFCARRY);\
	p->flag.unsetFlag(FlagRegister::CARRY);\
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
    p->flag.unsetFlag(FlagRegister::ZERO);
    p->flag.unsetFlag(FlagRegister::HALFCARRY);
    p->flag.unsetFlag(FlagRegister::CARRY);
    if (result == 0)
      p->flag.setFlag(FlagRegister::ZERO);
    p->flag.unsetFlag(FlagRegister::SUBTRACT);
    if (((p->A.value & 0xF) + (tmp & 0xF)) > 0xF)
      p->flag.setFlag(FlagRegister::HALFCARRY);
    if (val > 0xFF)
      p->flag.setFlag(FlagRegister::CARRY); 
    p->A.value = (result & 0xFF);
  }

void ADD_AX::exec(Processor *p)
{
  auto tmp = boost::get<uint8_t>(this->_args[0]);
  uint val = p->A.value + tmp;
  uint8_t result = static_cast<uint8_t>(val);
  p->flag.unsetFlag(FlagRegister::ZERO);
  p->flag.unsetFlag(FlagRegister::HALFCARRY);
  p->flag.unsetFlag(FlagRegister::CARRY);
  if (result == 0)
    p->flag.setFlag(FlagRegister::ZERO);
  p->flag.unsetFlag(FlagRegister::SUBTRACT);
  if (((p->A.value & 0xF) + (tmp & 0xF)) > 0xF)
    p->flag.setFlag(FlagRegister::HALFCARRY);
  if (val > 0xFF)
    p->flag.setFlag(FlagRegister::CARRY);
  p->A.value = (result & 0xFF);
}

#define ADD_HLXY_def(reg1, reg2)\
  void ADD_HL##reg1##reg2::exec(Processor *p)\
  {\
	uint16_t value_reg = make_word(p->reg2.value, p->reg1.value);\
	uint16_t hl = p->L.value | (p->H.value << 8);\
  	uint val = hl + value_reg;\
	uint16_t result = static_cast<uint16_t>(val);\
	p->flag.unsetFlag(FlagRegister::HALFCARRY);\
	p->flag.unsetFlag(FlagRegister::CARRY);\
	p->flag.unsetFlag(FlagRegister::SUBTRACT);\
	if (((hl & 0xFFF) + (value_reg & 0xFFF)) > 0xFFF)\
	  p->flag.setFlag(FlagRegister::HALFCARRY);\
	if ((val & 0x10000) != 0)\
	  p->flag.setFlag(FlagRegister::CARRY);	\
	p->H.value = get_high(result);\
	p->L.value = get_low(result);\
}

ADD_HLXY_def(B,C)
ADD_HLXY_def(D,E)
ADD_HLXY_def(H,L)

void ADD_HLSP::exec(Processor *p)
{
	uint16_t value_reg = p->SP.value;
	uint16_t hl = make_word(p->L.value, p->H.value);
  	uint val = hl + value_reg;
	uint16_t result = static_cast<uint16_t>(val);
	p->flag.unsetFlag(FlagRegister::HALFCARRY);
	p->flag.unsetFlag(FlagRegister::CARRY);
	p->flag.unsetFlag(FlagRegister::SUBTRACT);
	if (((hl & 0xFFF) + (value_reg & 0xFFF)) > 0xFFF)
	  p->flag.setFlag(FlagRegister::HALFCARRY);
	if ((val & 0x10000) != 0)
	  p->flag.setFlag(FlagRegister::CARRY);
	p->H.value = get_high(result);
	p->L.value = get_low(result);
}

void ADD_SPX::exec(Processor *p)
{
	uint8_t byte = boost::get<uint8_t>(this->_args[0]);
	uint16_t sp = p->SP.value;
	uint val = sp + byte;
	uint16_t result = static_cast<uint16_t>(val);
	p->flag.unsetFlag(FlagRegister::ZERO);
	p->flag.unsetFlag(FlagRegister::HALFCARRY);
	p->flag.unsetFlag(FlagRegister::CARRY);
	p->flag.unsetFlag(FlagRegister::SUBTRACT);
	if (((sp ^ byte ^ (result & 0xFFFF)) & 0x10) == 0x10)
	  p->flag.setFlag(FlagRegister::HALFCARRY);
	if (((sp ^ byte ^ (result & 0xFFFF)) & 0x100) == 0x100)
	  p->flag.setFlag(FlagRegister::CARRY);
	p->SP.value = (result & 0xFF);
}

//ADC instructions

#define ADC_XY_def(reg1, reg2)			\
  void ADC_##reg1##reg2::exec(Processor *p)\
  {\
    uint val = p->reg1.value + p->reg2.value + p->flag.getFlag(FlagRegister::CARRY);\
    uint8_t result = static_cast<uint8_t>(val);\
    p->flag.unsetFlag(FlagRegister::ZERO);\
    p->flag.unsetFlag(FlagRegister::HALFCARRY);\
    p->flag.unsetFlag(FlagRegister::CARRY);\
    if (result == 0)\
      p->flag.setFlag(FlagRegister::ZERO);\
    p->flag.unsetFlag(FlagRegister::SUBTRACT);\
    if (((p->reg1.value & 0xF) + (p->reg2.value & 0xF) + p->flag.getFlag(FlagRegister::CARRY)) > 0xF) \
      p->flag.setFlag(FlagRegister::HALFCARRY);\
    if (val > 0xFF)\
      p->flag.setFlag(FlagRegister::CARRY);\
    p->reg1.value = result;	   \
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
    p->flag.unsetFlag(FlagRegister::ZERO);
    p->flag.unsetFlag(FlagRegister::HALFCARRY);
    p->flag.unsetFlag(FlagRegister::CARRY);
    if (result == 0)
      p->flag.setFlag(FlagRegister::ZERO);	
    p->flag.unsetFlag(FlagRegister::SUBTRACT);
    if (((p->A.value & 0xF) + (tmp & 0xF) + p->flag.getFlag(FlagRegister::CARRY)) > 0xF) 
      p->flag.setFlag(FlagRegister::HALFCARRY);
    if (val > 0xFF)
      p->flag.setFlag(FlagRegister::CARRY);
    p->A.value = result;       
}

void ADC_AX::exec(Processor *p)
{
  auto tmp = boost::get<uint8_t>(this->_args[0]); 
  uint val = p->A.value + tmp + p->flag.getFlag(FlagRegister::CARRY);
  uint8_t result = static_cast<uint8_t>(val);
  p->flag.unsetFlag(FlagRegister::ZERO);
  p->flag.unsetFlag(FlagRegister::HALFCARRY);
  p->flag.unsetFlag(FlagRegister::CARRY);
  if (result == 0)
    p->flag.setFlag(FlagRegister::ZERO);
  p->flag.unsetFlag(FlagRegister::SUBTRACT);
  if (((p->A.value & 0xF) + (tmp & 0xF) + p->flag.getFlag(FlagRegister::CARRY)) > 0xF)
    p->flag.setFlag(FlagRegister::HALFCARRY);
  if (val > 0xFF)
    p->flag.setFlag(FlagRegister::CARRY);
  p->A.value = result;
}  

//SUB instructions

#define SUB_XY_def(reg1, reg2)                  \
  void SUB_##reg1##reg2::exec(Processor *p)\
  {\
    uint val = p->reg1.value - p->reg2.value;\
    uint8_t result = static_cast<uint8_t>(val);\
    p->flag.unsetFlag(FlagRegister::ZERO);\
    p->flag.unsetFlag(FlagRegister::HALFCARRY);\
    p->flag.unsetFlag(FlagRegister::CARRY);\
    if (result == 0)\
      p->flag.setFlag(FlagRegister::ZERO);\
    p->flag.setFlag(FlagRegister::SUBTRACT);\
    if (((p->reg1.value & 0xF) - (p->reg2.value & 0xF)) < 0) \
      p->flag.setFlag(FlagRegister::HALFCARRY);\
    if (p->reg1.value < p->reg2.value)		       \
      p->flag.setFlag(FlagRegister::CARRY);\
    p->reg1.value = result;       \
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
    p->flag.unsetFlag(FlagRegister::ZERO);
    p->flag.unsetFlag(FlagRegister::HALFCARRY);
    p->flag.unsetFlag(FlagRegister::CARRY);
    if (result == 0)
      p->flag.setFlag(FlagRegister::ZERO);
    p->flag.setFlag(FlagRegister::SUBTRACT);
    if (((p->A.value & 0xF) - (tmp & 0xF)) < 0)
      p->flag.setFlag(FlagRegister::HALFCARRY);
    if (p->A.value < tmp)                 
      p->flag.setFlag(FlagRegister::CARRY);
    p->A.value = result;       
}


void SUB_AX::exec(Processor *p)
{
  auto tmp = boost::get<uint8_t>(this->_args[0]);    
  uint val = p->A.value - tmp;
  uint8_t result = static_cast<uint8_t>(val);
  p->flag.unsetFlag(FlagRegister::ZERO);
  p->flag.unsetFlag(FlagRegister::HALFCARRY);
  p->flag.unsetFlag(FlagRegister::CARRY);
  if (result == 0)
    p->flag.setFlag(FlagRegister::ZERO);
  p->flag.setFlag(FlagRegister::SUBTRACT);
  if (((p->A.value & 0xF) - (tmp & 0xF)) < 0)
    p->flag.setFlag(FlagRegister::HALFCARRY);
  if (p->A.value < tmp)
    p->flag.setFlag(FlagRegister::CARRY);
  p->A.value = result;
}

//SBC instructions

#define SBC_XY_def(reg1, reg2)                  \
  void SBC_##reg1##reg2::exec(Processor *p)\
  {\
    uint val = p->reg1.value - p->reg2.value - p->flag.getFlag(FlagRegister::CARRY); \
    uint8_t result = static_cast<uint8_t>(val);\
    p->flag.unsetFlag(FlagRegister::ZERO);\
    p->flag.unsetFlag(FlagRegister::HALFCARRY);\
    p->flag.unsetFlag(FlagRegister::CARRY);\
    if (result == 0)\
      p->flag.setFlag(FlagRegister::ZERO);\
    p->flag.setFlag(FlagRegister::SUBTRACT);\
    if (((p->reg1.value & 0xF) - (p->reg2.value & 0xF) - p->flag.getFlag(FlagRegister::CARRY)) < 0) \
      p->flag.setFlag(FlagRegister::HALFCARRY);\
    if (p->reg1.value < p->reg2.value)                 \
      p->flag.setFlag(FlagRegister::CARRY);\
    p->reg1.value = result;       \
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
  p->flag.unsetFlag(FlagRegister::ZERO);
  p->flag.unsetFlag(FlagRegister::HALFCARRY);
  p->flag.unsetFlag(FlagRegister::CARRY);
  if (result == 0)
    p->flag.setFlag(FlagRegister::ZERO);
  p->flag.setFlag(FlagRegister::SUBTRACT);
  if (((p->A.value & 0xF) - (tmp & 0xF) - p->flag.getFlag(FlagRegister::CARRY)) < 0) 
    p->flag.setFlag(FlagRegister::HALFCARRY);
  if (p->A.value < tmp)                 
    p->flag.setFlag(FlagRegister::CARRY);
  p->A.value = result;       
}

void SBC_AX::exec(Processor *p)
{
  auto tmp = boost::get<uint8_t>(this->_args[0]);
  uint val = p->A.value - tmp - p->flag.getFlag(FlagRegister::CARRY);
  uint8_t result = static_cast<uint8_t>(val);
  p->flag.unsetFlag(FlagRegister::ZERO);
  p->flag.unsetFlag(FlagRegister::HALFCARRY);
  p->flag.unsetFlag(FlagRegister::CARRY);
  if (result == 0)
    p->flag.setFlag(FlagRegister::ZERO);
  p->flag.setFlag(FlagRegister::SUBTRACT);
  if (((p->A.value & 0xF) - (tmp & 0xF) - p->flag.getFlag(FlagRegister::CARRY)) < 0)
    p->flag.setFlag(FlagRegister::HALFCARRY);
  if (p->A.value < tmp)
    p->flag.setFlag(FlagRegister::CARRY);
  p->A.value = result;
}

//AND instructions

#define AND_XY_def(reg1, reg2)                  \
  void AND_##reg1##reg2::exec(Processor *p)\
  {\
    p->reg1.value &= p->reg2.value; \
    p->flag.unsetFlag(FlagRegister::ZERO); \
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
  p->flag.unsetFlag(FlagRegister::ZERO);
  if (p->A.value == 0)
    p->flag.setFlag(FlagRegister::ZERO);
  p->flag.unsetFlag(FlagRegister::SUBTRACT);
  p->flag.setFlag(FlagRegister::HALFCARRY);
  p->flag.unsetFlag(FlagRegister::CARRY);
}

void AND_AX::exec(Processor *p)
{
  auto tmp = boost::get<uint8_t>(this->_args[0]);
  p->A.value &= tmp;
  p->flag.unsetFlag(FlagRegister::ZERO);
  if (p->A.value == 0)
    p->flag.setFlag(FlagRegister::ZERO);
  p->flag.unsetFlag(FlagRegister::SUBTRACT);
  p->flag.setFlag(FlagRegister::HALFCARRY);
  p->flag.unsetFlag(FlagRegister::CARRY);
} 

//OR instructions

#define OR_XY_def(reg1, reg2)                  \
  void OR_##reg1##reg2::exec(Processor *p)\
  {\
    p->reg1.value |= p->reg2.value; \
    p->flag.unsetFlag(FlagRegister::ZERO); \
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
  p->flag.unsetFlag(FlagRegister::ZERO);
  if (p->A.value == 0)
    p->flag.setFlag(FlagRegister::ZERO);
  p->flag.unsetFlag(FlagRegister::SUBTRACT);
  p->flag.unsetFlag(FlagRegister::HALFCARRY);
  p->flag.unsetFlag(FlagRegister::CARRY);
}

void OR_AX::exec(Processor *p)
{
  auto tmp = boost::get<uint8_t>(this->_args[0]);
  p->A.value |= tmp;
  p->flag.unsetFlag(FlagRegister::ZERO);
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
    p->flag.unsetFlag(FlagRegister::ZERO); \
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
  p->flag.unsetFlag(FlagRegister::ZERO);
  if (p->A.value == 0)
    p->flag.setFlag(FlagRegister::ZERO);
  p->flag.unsetFlag(FlagRegister::SUBTRACT);
  p->flag.unsetFlag(FlagRegister::HALFCARRY);
  p->flag.unsetFlag(FlagRegister::CARRY);
}

void XOR_AX::exec(Processor *p)
{
  auto tmp = boost::get<uint8_t>(this->_args[0]); 
  p->A.value ^= tmp;
  p->flag.unsetFlag(FlagRegister::ZERO);
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
    p->flag.unsetFlag(FlagRegister::ZERO);\
    p->flag.unsetFlag(FlagRegister::HALFCARRY);\
    p->flag.unsetFlag(FlagRegister::CARRY);\
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
    p->flag.unsetFlag(FlagRegister::ZERO);
    p->flag.unsetFlag(FlagRegister::HALFCARRY);
    p->flag.unsetFlag(FlagRegister::CARRY);
    if (result == 0)
      p->flag.setFlag(FlagRegister::ZERO);
    p->flag.setFlag(FlagRegister::SUBTRACT);
    if (((p->A.value & 0xF) - (tmp & 0xF)) < 0)
      p->flag.setFlag(FlagRegister::HALFCARRY);
    if (p->A.value < tmp)                 
      p->flag.setFlag(FlagRegister::CARRY);
}

void CP_AX::exec(Processor *p)
{
  auto tmp = boost::get<uint8_t>(this->_args[0]);
  uint val = p->A.value - tmp;
  uint8_t result = static_cast<uint8_t>(val);
  p->flag.unsetFlag(FlagRegister::ZERO);
  p->flag.unsetFlag(FlagRegister::HALFCARRY);
  p->flag.unsetFlag(FlagRegister::CARRY);
  if (result == 0)
    p->flag.setFlag(FlagRegister::ZERO);
  p->flag.setFlag(FlagRegister::SUBTRACT);
  if (((p->A.value & 0xF) - (tmp & 0xF)) < 0)
    p->flag.setFlag(FlagRegister::HALFCARRY);
  if (p->A.value < tmp)
    p->flag.setFlag(FlagRegister::CARRY);
}  

// INC instructions

#define INC_Reg_def(reg)                  \
  void INC_##reg::exec(Processor *p)\
  {\
    p->flag.unsetFlag(FlagRegister::ZERO);\
    p->flag.unsetFlag(FlagRegister::HALFCARRY);\
    p->reg.value += 1;\
    if (p->reg.value == 0)\
      p->flag.setFlag(FlagRegister::ZERO);\
    p->flag.unsetFlag(FlagRegister::SUBTRACT);\
    if ((p->reg.value & 0xF) == 0x00) \
      p->flag.setFlag(FlagRegister::HALFCARRY);\
  }

INC_Reg_def(A)
INC_Reg_def(B)
INC_Reg_def(C)
INC_Reg_def(D)
INC_Reg_def(E)
INC_Reg_def(H)
INC_Reg_def(L)


#define INC_DReg_def(reg1, reg2)\
  void INC_##reg1##reg2::exec(Processor *p)\
  {\
	uint16_t value = make_word(p->reg2.value, p->reg1.value);\
	++value;\
	uint8_t reg1_val = get_high(value);\
	uint8_t reg2_val = get_low(value);\
	p->reg1.value = reg1_val;\
	p->reg2.value = reg2_val;\
  }

INC_DReg_def(B,C)
INC_DReg_def(D,E)
INC_DReg_def(H,L)

void INC_SP::exec(Processor *p)
{
  uint16_t value = p->SP.value;
  ++value;
  p->SP.value = value;
}


void INC_HLdereference::exec(Processor *p)
{
  auto tmp = HLReadDereference(p);
  tmp += 1;
  p->flag.unsetFlag(FlagRegister::ZERO);
  p->flag.unsetFlag(FlagRegister::HALFCARRY);
  if (tmp == 0)
    p->flag.setFlag(FlagRegister::ZERO);
  p->flag.unsetFlag(FlagRegister::SUBTRACT);
  if ((tmp & 0xF) == 0x00)
    p->flag.setFlag(FlagRegister::HALFCARRY);
  HLWriteDereference(p, tmp);
} 

// DEC instructions

#define DEC_Reg_def(reg)                  \
  void DEC_##reg::exec(Processor *p)\
  {\
    p->flag.unsetFlag(FlagRegister::ZERO);\
    p->flag.unsetFlag(FlagRegister::HALFCARRY);\
    p->reg.value -= 1;\
    if (p->reg.value == 0) {\
      p->flag.setFlag(FlagRegister::ZERO);\
	}\
    p->flag.setFlag(FlagRegister::SUBTRACT);\
    if ((p->reg.value & 0xF) == 0x0F) \
      p->flag.setFlag(FlagRegister::HALFCARRY);\
  }

DEC_Reg_def(A)
DEC_Reg_def(B)
DEC_Reg_def(C)
DEC_Reg_def(D)
DEC_Reg_def(E)
DEC_Reg_def(H)
DEC_Reg_def(L)

#define DEC_DReg_def(reg1, reg2)\
  void DEC_##reg1##reg2::exec(Processor *p)\
  {\
	uint16_t value = make_word(p->reg2.value, p->reg1.value);\
	--value;\
	uint8_t reg1_val = get_high(value);\
	uint8_t reg2_val = get_low(value);\
	p->reg1.value = reg1_val;\
	p->reg2.value = reg2_val;\
  }

DEC_DReg_def(B,C)
DEC_DReg_def(D,E)
DEC_DReg_def(H,L)

void DEC_SP::exec(Processor *p)
{
  uint16_t value = p->SP.value;
  --value;
  p->SP.value = value;
}

void DEC_HLdereference::exec(Processor *p)
{
  auto tmp = HLReadDereference(p);
  tmp -= 1;
  p->flag.unsetFlag(FlagRegister::ZERO);
  p->flag.unsetFlag(FlagRegister::HALFCARRY);
  if (tmp == 0)
    p->flag.setFlag(FlagRegister::ZERO);
  p->flag.setFlag(FlagRegister::SUBTRACT);
  if ((tmp & 0xF) == 0x0F)
    p->flag.setFlag(FlagRegister::HALFCARRY);
  HLWriteDereference(p, tmp);
}

// SWAP instructions

#define SWAP_RegX_def(reg)                  \
  void SWAP_##reg##X::exec(Processor *p)\
  {\
    p->flag.unsetFlag(FlagRegister::ZERO);\
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

void SWAP_HL::exec(Processor *p)
{
  p->flag.unsetFlag(FlagRegister::ZERO);
  auto tmp = HLReadDereference(p);
  auto a = tmp >> 4;                 \
  auto b = tmp << 4;
  auto temp = a | b;
  if (temp == 0)
    p->flag.setFlag(FlagRegister::ZERO);
  p->flag.unsetFlag(FlagRegister::SUBTRACT);
  p->flag.unsetFlag(FlagRegister::HALFCARRY);
  p->flag.unsetFlag(FlagRegister::CARRY);
  HLWriteDereference(p, temp);
}


#define DAA_def()                  \
  void DAA::exec(Processor *p)\
  {\
    p->flag.unsetFlag(FlagRegister::CARRY);\
    p->flag.unsetFlag(FlagRegister::ZERO);\
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

#define BIT_BITX_def(bit, reg)		\
  void BIT_##bit##reg::exec(Processor *p)\
  {\
    p->flag.unsetFlag(FlagRegister::ZERO);\
    if (!(p->reg.value & (1 << bit)))\
      p->flag.setFlag(FlagRegister::Flag::ZERO);\
    p->flag.setFlag(FlagRegister::Flag::HALFCARRY);\
  }

BIT_BITX_def(0, A)
BIT_BITX_def(1, A)
BIT_BITX_def(2, A)
BIT_BITX_def(3, A)
BIT_BITX_def(4, A)
BIT_BITX_def(5, A)
BIT_BITX_def(6, A)
BIT_BITX_def(7, A)
BIT_BITX_def(0, B)
BIT_BITX_def(1, B)
BIT_BITX_def(2, B)
BIT_BITX_def(3, B)
BIT_BITX_def(4, B)
BIT_BITX_def(5, B)
BIT_BITX_def(6, B)
BIT_BITX_def(7, B)
BIT_BITX_def(0, C)
BIT_BITX_def(1, C)
BIT_BITX_def(2, C)
BIT_BITX_def(3, C)
BIT_BITX_def(4, C)
BIT_BITX_def(5, C)
BIT_BITX_def(6, C)
BIT_BITX_def(7, C)
BIT_BITX_def(0, D)
BIT_BITX_def(1, D)
BIT_BITX_def(2, D)
BIT_BITX_def(3, D)
BIT_BITX_def(4, D)
BIT_BITX_def(5, D)
BIT_BITX_def(6, D)
BIT_BITX_def(7, D)
BIT_BITX_def(0, E)
BIT_BITX_def(1, E)
BIT_BITX_def(2, E)
BIT_BITX_def(3, E)
BIT_BITX_def(4, E)
BIT_BITX_def(5, E)
BIT_BITX_def(6, E)
BIT_BITX_def(7, E)
BIT_BITX_def(0, H)
BIT_BITX_def(1, H)
BIT_BITX_def(2, H)
BIT_BITX_def(3, H)
BIT_BITX_def(4, H)
BIT_BITX_def(5, H)
BIT_BITX_def(6, H)
BIT_BITX_def(7, H)
BIT_BITX_def(0, L)
BIT_BITX_def(1, L)
BIT_BITX_def(2, L)
BIT_BITX_def(3, L)
BIT_BITX_def(4, L)
BIT_BITX_def(5, L)
BIT_BITX_def(6, L)
BIT_BITX_def(7, L)

#define BIT_BITHL_def(bit)          \
  void BIT_##bit##HL::exec(Processor *p)\
  {\
    p->flag.unsetFlag(FlagRegister::ZERO);\
    auto tmp = HLReadDereference(p);\
    if (tmp & (1 << bit))\
      p->flag.setFlag(FlagRegister::Flag::ZERO);\
    p->flag.unsetFlag(FlagRegister::Flag::SUBTRACT);\
    p->flag.setFlag(FlagRegister::Flag::HALFCARRY);\
 }

BIT_BITHL_def(0)
BIT_BITHL_def(1)
BIT_BITHL_def(2)
BIT_BITHL_def(3)
BIT_BITHL_def(4)
BIT_BITHL_def(5)
BIT_BITHL_def(6)
BIT_BITHL_def(7)


#define SET_BITX_def(bit, reg)          \
  void SET_##bit##reg::exec(Processor *p)\
  {\
    auto tmp = set_bit(p->reg.value, bit);\
    p->reg.value = tmp;\
  }

SET_BITX_def(0, A)
SET_BITX_def(1, A)
SET_BITX_def(2, A)
SET_BITX_def(3, A)
SET_BITX_def(4, A)
SET_BITX_def(5, A)
SET_BITX_def(6, A)
SET_BITX_def(7, A)
SET_BITX_def(0, B)
SET_BITX_def(1, B)
SET_BITX_def(2, B)
SET_BITX_def(3, B)
SET_BITX_def(4, B)
SET_BITX_def(5, B)
SET_BITX_def(6, B)
SET_BITX_def(7, B)
SET_BITX_def(0, C)
SET_BITX_def(1, C)
SET_BITX_def(2, C)
SET_BITX_def(3, C)
SET_BITX_def(4, C)
SET_BITX_def(5, C)
SET_BITX_def(6, C)
SET_BITX_def(7, C)
SET_BITX_def(0, D)
SET_BITX_def(1, D)
SET_BITX_def(2, D)
SET_BITX_def(3, D)
SET_BITX_def(4, D)
SET_BITX_def(5, D)
SET_BITX_def(6, D)
SET_BITX_def(7, D)
SET_BITX_def(0, E)
SET_BITX_def(1, E)
SET_BITX_def(2, E)
SET_BITX_def(3, E)
SET_BITX_def(4, E)
SET_BITX_def(5, E)
SET_BITX_def(6, E)
SET_BITX_def(7, E)
SET_BITX_def(0, H)
SET_BITX_def(1, H)
SET_BITX_def(2, H)
SET_BITX_def(3, H)
SET_BITX_def(4, H)
SET_BITX_def(5, H)
SET_BITX_def(6, H)
SET_BITX_def(7, H)
SET_BITX_def(0, L)
SET_BITX_def(1, L)
SET_BITX_def(2, L)
SET_BITX_def(3, L)
SET_BITX_def(4, L)
SET_BITX_def(5, L)
SET_BITX_def(6, L)
SET_BITX_def(7, L)


#define SET_BITHL_def(bit)          \
  void SET_##bit##HL::exec(Processor *p)\
  {\
    auto tmp = HLReadDereference(p);\
    auto temp = set_bit(tmp, bit);\
    HLWriteDereference(p, temp);\
  }

SET_BITHL_def(0)
SET_BITHL_def(1)
SET_BITHL_def(2)
SET_BITHL_def(3)
SET_BITHL_def(4)
SET_BITHL_def(5)
SET_BITHL_def(6)
SET_BITHL_def(7)


#define RES_BITX_def(bit, reg)          \
  void RES_##bit##reg::exec(Processor *p)\
  {\
    auto tmp = clear_bit(p->reg.value, bit);\
    p->reg.value = tmp;\
  }

RES_BITX_def(0, A)
RES_BITX_def(1, A)
RES_BITX_def(2, A)
RES_BITX_def(3, A)
RES_BITX_def(4, A)
RES_BITX_def(5, A)
RES_BITX_def(6, A)
RES_BITX_def(7, A)
RES_BITX_def(0, B)
RES_BITX_def(1, B)
RES_BITX_def(2, B)
RES_BITX_def(3, B)
RES_BITX_def(4, B)
RES_BITX_def(5, B)
RES_BITX_def(6, B)
RES_BITX_def(7, B)
RES_BITX_def(0, C)
RES_BITX_def(1, C)
RES_BITX_def(2, C)
RES_BITX_def(3, C)
RES_BITX_def(4, C)
RES_BITX_def(5, C)
RES_BITX_def(6, C)
RES_BITX_def(7, C)
RES_BITX_def(0, D)
RES_BITX_def(1, D)
RES_BITX_def(2, D)
RES_BITX_def(3, D)
RES_BITX_def(4, D)
RES_BITX_def(5, D)
RES_BITX_def(6, D)
RES_BITX_def(7, D)
RES_BITX_def(0, E)
RES_BITX_def(1, E)
RES_BITX_def(2, E)
RES_BITX_def(3, E)
RES_BITX_def(4, E)
RES_BITX_def(5, E)
RES_BITX_def(6, E)
RES_BITX_def(7, E)
RES_BITX_def(0, H)
RES_BITX_def(1, H)
RES_BITX_def(2, H)
RES_BITX_def(3, H)
RES_BITX_def(4, H)
RES_BITX_def(5, H)
RES_BITX_def(6, H)
RES_BITX_def(7, H)
RES_BITX_def(0, L)
RES_BITX_def(1, L)
RES_BITX_def(2, L)
RES_BITX_def(3, L)
RES_BITX_def(4, L)
RES_BITX_def(5, L)
RES_BITX_def(6, L)
RES_BITX_def(7, L)

#define RES_BITHL_def(bit)          \
  void RES_##bit##HL::exec(Processor *p)\
  {\
    auto tmp = HLReadDereference(p);\
    auto temp = clear_bit(tmp, bit);\
    HLWriteDereference(p, temp);\
  }

RES_BITHL_def(0)
RES_BITHL_def(1)
RES_BITHL_def(2)
RES_BITHL_def(3)
RES_BITHL_def(4)
RES_BITHL_def(5)
RES_BITHL_def(6)
RES_BITHL_def(7)


void RRCA::exec(Processor *p)
{
	p->flag.unsetFlag(FlagRegister::ZERO);
	auto flag_carry = check_bit(p->A.value, 0);
	auto truncated_bit = check_bit(p->A.value, 0);
	auto temp = static_cast<uint8_t>((p->A.value >> 1)
					 | (truncated_bit << 7));
	p->A.value = temp;
	if (p->A.value == 0)
		p->flag.setFlag(FlagRegister::ZERO);
	p->flag.unsetFlag(FlagRegister::SUBTRACT);
	p->flag.unsetFlag(FlagRegister::HALFCARRY);
	if (flag_carry)
		p->flag.setFlag(FlagRegister::CARRY);
	else
		p->flag.unsetFlag(FlagRegister::CARRY);
}


#define RRC_RegX_def(reg)                  \
  void RRC_##reg##X::exec(Processor *p)\
  {\
    p->flag.unsetFlag(FlagRegister::ZERO);\
    auto flag_carry = check_bit(p->reg.value, 0);\
    auto truncated_bit = check_bit(p->reg.value, 0);\
    auto temp = static_cast<uint8_t>((p->reg.value >> 1)\
					| (truncated_bit << 7));\
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


void RRC_HL::exec(Processor *p)
{
    p->flag.unsetFlag(FlagRegister::ZERO);
    auto tmp = HLReadDereference(p);
    auto flag_carry = check_bit(tmp, 0);
    auto truncated_bit = check_bit(tmp, 0);
    auto temp = static_cast<uint8_t>((tmp >> 1) | (truncated_bit << 7));
    if (temp == 0)
      p->flag.setFlag(FlagRegister::ZERO);
    p->flag.unsetFlag(FlagRegister::SUBTRACT);
    p->flag.unsetFlag(FlagRegister::HALFCARRY);
    if (flag_carry)
      p->flag.setFlag(FlagRegister::CARRY);
    else
      p->flag.unsetFlag(FlagRegister::CARRY);
    HLWriteDereference(p, temp);
}

void RLCA::exec(Processor *p)
{
	p->flag.unsetFlag(FlagRegister::ZERO);
	auto flag_carry = check_bit(p->A.value, 7);
	auto truncated_bit = check_bit(p->A.value, 7);
	auto temp = static_cast<uint8_t>((p->A.value << 1) | truncated_bit);
	p->A.value = temp;
	if (p->A.value == 0)
		p->flag.setFlag(FlagRegister::ZERO);
	p->flag.unsetFlag(FlagRegister::SUBTRACT);
	p->flag.unsetFlag(FlagRegister::HALFCARRY);
	if (flag_carry)
		p->flag.setFlag(FlagRegister::CARRY);
	else
		p->flag.unsetFlag(FlagRegister::CARRY);
}

#define RLC_RegX_def(reg)                  \
  void RLC_##reg##X::exec(Processor *p)\
  {\
    p->flag.unsetFlag(FlagRegister::ZERO);\
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

void RLC_HL::exec(Processor *p)
{
    p->flag.unsetFlag(FlagRegister::ZERO);
    auto tmp = HLReadDereference(p);
    auto flag_carry = check_bit(tmp, 7);
    auto truncated_bit = check_bit(tmp, 7);
    auto temp = static_cast<uint8_t>((tmp << 1) | truncated_bit);
    if (temp == 0)
      p->flag.setFlag(FlagRegister::ZERO);
    p->flag.unsetFlag(FlagRegister::SUBTRACT);
    p->flag.unsetFlag(FlagRegister::HALFCARRY);
    if (flag_carry)
      p->flag.setFlag(FlagRegister::CARRY);
    else
      p->flag.unsetFlag(FlagRegister::CARRY);
    HLWriteDereference(p, temp);
}


void RLA::exec(Processor *p)
{
	p->flag.unsetFlag(FlagRegister::ZERO);
	auto carry = p->flag.getFlag(FlagRegister::CARRY);
	auto flag_carry = check_bit(p->A.value, 7);
	if (flag_carry)
		p->flag.setFlag(FlagRegister::CARRY);
	else
		p->flag.unsetFlag(FlagRegister::CARRY);
	auto temp = static_cast<uint8_t>(p->A.value << 1);
	temp |= carry;
	if (temp == 0)
		p->flag.setFlag(FlagRegister::ZERO);
	p->flag.unsetFlag(FlagRegister::SUBTRACT);
	p->flag.unsetFlag(FlagRegister::HALFCARRY);
	p->A.value = temp;
}


#define RL_RegX_def(reg)                  \
  void RL_##reg##X::exec(Processor *p)\
  {\
    p->flag.unsetFlag(FlagRegister::ZERO);\
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


void RL_HL::exec(Processor *p)
{
    p->flag.unsetFlag(FlagRegister::ZERO); 
    auto tmp = HLReadDereference(p);
    auto carry = p->flag.getFlag(FlagRegister::CARRY);
    auto flag_carry = check_bit(tmp, 7);
    if (flag_carry)
      p->flag.setFlag(FlagRegister::CARRY);
    else
      p->flag.unsetFlag(FlagRegister::CARRY);
    auto temp = static_cast<uint8_t>(tmp << 1);
    temp |= carry;
    if (temp == 0)
      p->flag.setFlag(FlagRegister::ZERO);
    p->flag.unsetFlag(FlagRegister::SUBTRACT);
    p->flag.unsetFlag(FlagRegister::HALFCARRY);
    HLWriteDereference(p, temp);
}


void RRA::exec(Processor *p)
{
	p->flag.unsetFlag(FlagRegister::ZERO);
	auto carry = p->flag.getFlag(FlagRegister::CARRY);
	auto flag_carry = check_bit(p->A.value, 0);
	if (flag_carry)
		p->flag.setFlag(FlagRegister::CARRY);
	else
		p->flag.unsetFlag(FlagRegister::CARRY);
	auto temp = static_cast<uint8_t>(p->A.value >> 1);
	temp |= carry;
	if (temp == 0)
		p->flag.setFlag(FlagRegister::ZERO);
	p->flag.unsetFlag(FlagRegister::SUBTRACT);
	p->flag.unsetFlag(FlagRegister::HALFCARRY);
	p->A.value = temp;
}


#define RR_RegX_def(reg)                  \
  void RR_##reg##X::exec(Processor *p)\
  {\
   p->flag.unsetFlag(FlagRegister::ZERO);\
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


void RR_HL::exec(Processor *p)
{
    p->flag.unsetFlag(FlagRegister::ZERO);
    auto tmp = HLReadDereference(p);
    auto carry = p->flag.getFlag(FlagRegister::CARRY);
    auto flag_carry = check_bit(tmp, 0);
    if (flag_carry)
      p->flag.setFlag(FlagRegister::CARRY);
    else
      p->flag.unsetFlag(FlagRegister::CARRY);
    auto temp = static_cast<uint8_t>(tmp >> 1);
    temp |= carry;
    if (temp == 0)
      p->flag.setFlag(FlagRegister::ZERO);
    p->flag.unsetFlag(FlagRegister::SUBTRACT);
    p->flag.unsetFlag(FlagRegister::HALFCARRY);
    HLWriteDereference(p, temp);
}

#define SLA_RegX_def(reg)                  \
  void SLA_##reg##X::exec(Processor *p)\
  {\
    p->flag.unsetFlag(FlagRegister::ZERO);\
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


void SLA_HL::exec(Processor *p)
{
    p->flag.unsetFlag(FlagRegister::ZERO);
    auto tmp = HLReadDereference(p);
    auto flag_carry = check_bit(tmp, 7);
    if (flag_carry)
      p->flag.setFlag(FlagRegister::CARRY);
    else
      p->flag.unsetFlag(FlagRegister::CARRY);
    auto temp = static_cast<uint8_t>(tmp << 1);
    if (temp == 0)
      p->flag.setFlag(FlagRegister::ZERO);
    p->flag.unsetFlag(FlagRegister::SUBTRACT);
    p->flag.unsetFlag(FlagRegister::HALFCARRY);
    HLWriteDereference(p, temp);
}

#define SRA_RegX_def(reg)                  \
  void SRA_##reg##X::exec(Processor *p)\
  {\
    p->flag.unsetFlag(FlagRegister::ZERO);\
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


void SRA_HL::exec(Processor *p)
{
    p->flag.unsetFlag(FlagRegister::ZERO);
    auto tmp = HLReadDereference(p);
    auto bit_carry = check_bit(tmp, 0);
    auto top_bit = check_bit(tmp, 7);
    auto temp = static_cast<uint8_t>(tmp >> 1);
    temp = set_bit_to(temp, 7, top_bit);
    if (temp == 0)
      p->flag.setFlag(FlagRegister::ZERO);
    if (bit_carry)
      p->flag.setFlag(FlagRegister::CARRY);
    else
      p->flag.unsetFlag(FlagRegister::CARRY);
    p->flag.unsetFlag(FlagRegister::SUBTRACT);
    p->flag.unsetFlag(FlagRegister::HALFCARRY);
    HLWriteDereference(p, temp);
}

#define SRL_RegX_def(reg)                  \
  void SRL_##reg##X::exec(Processor *p)\
  {\
    p->flag.unsetFlag(FlagRegister::ZERO);\
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

void SRL_HL::exec(Processor *p)
{
    p->flag.unsetFlag(FlagRegister::ZERO); 
    auto tmp = HLReadDereference(p);
    bool leastbitset = check_bit(tmp, 0);
    auto temp = static_cast<uint8_t>(tmp >> 1);
    if (temp == 0)
      p->flag.setFlag(FlagRegister::ZERO);
    if (leastbitset)
      p->flag.setFlag(FlagRegister::CARRY);
    else
      p->flag.unsetFlag(FlagRegister::CARRY);
    p->flag.unsetFlag(FlagRegister::SUBTRACT);
    p->flag.unsetFlag(FlagRegister::HALFCARRY);
    HLWriteDereference(p, temp);
}

void HALT::exec(Processor *p)
{
  p->HALT();
}

void STOP::exec(Processor *p)
{
  p->STOP();
}

void EI::exec(Processor *p)
{
  p->enableIME();
}

void DI::exec(Processor *p)
{
  p->disableIME();
}

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
	p->PC.value = make_word(p->L.value, p->H.value);
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
	if ( p->flag.getFlag(FlagRegister::ZERO)) {
		int8_t t = (int8_t) boost::get<uint8_t>(this->_args[0]);
		p->PC.value += t;
	}
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


/////////////////////////////////////
/////////////// RESET ///////////////
/////////////////////////////////////

#define RST_def(x) \
	void RST_##x::exec(Processor *p) \
	{\
		_callPush(p);\
		p->PC.value = x;\
	}

RST_def(0x00)
RST_def(0x08)
RST_def(0x10)
RST_def(0x18)
RST_def(0x20)
RST_def(0x28)
RST_def(0x30)
RST_def(0x38)

/////////////////////////////////////
////////////// RETURNS //////////////
/////////////////////////////////////


void RET::exec(Processor *p)
{
	_return(p);
}

void RETNZ::exec(Processor *p)
{
	if ( !p->flag.getFlag(FlagRegister::ZERO))
		_return(p);
}

void RETZ::exec(Processor *p)
{
	if ( p->flag.getFlag(FlagRegister::ZERO))
		_return(p);
}

void RETNC::exec(Processor *p)
{
	if ( !p->flag.getFlag(FlagRegister::CARRY))
		_return(p);
}

void RETC::exec(Processor *p)
{
	if ( p->flag.getFlag(FlagRegister::CARRY))
		_return(p);
}

void RETI::exec(Processor *p)
{
  _return(p);
  p->enableIME();
}
