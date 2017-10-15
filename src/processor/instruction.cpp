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


//ADD instructions

void ADD_AA::exec(Processor *p)
{
  	auto val = p->A.value * 2;
	if ((val & 0xFF) == 0)
	  p->flag.setFlag(FlagRegister::ZERO);			         /// IF result = 0 so set Z 
	p->flag.unsetFlag(FlagRegister::SUBTRACT);               /// reset N
	if (((p->A.value & 0xF) + (p->A.value & 0xF)) > 0xF)     /// Set if carry from bit 3
	  p->flag.setFlag(FlagRegister::HALFCARRY);
	if (val > 0xFF)                                          /// Set if carry from bit 7
	  p->flag.setFlag(FlagRegister::CARRY);

	p->A.value = (val & 0xFF);
}

void ADD_AB::exec(Processor *p)
{
  	auto val = p->A.value + p->B.value;

	if ((val & 0xFF) == 0)
	  p->flag.setFlag(FlagRegister::ZERO);                   
	p->flag.unsetFlag(FlagRegister::SUBTRACT);               
	if (((p->A.value & 0xF) + (p->B.value & 0xF)) > 0xF)     
	  p->flag.setFlag(FlagRegister::HALFCARRY);
	if (val > 0xFF)                                          
	  p->flag.setFlag(FlagRegister::CARRY);

	p->A.value = (val & 0xFF);
}  


void ADD_AC::exec(Processor *p)
{
  	auto val = p->A.value + p->C.value;
	if ((val & 0xFF) == 0)
	  p->flag.setFlag(FlagRegister::ZERO);                   
	p->flag.unsetFlag(FlagRegister::SUBTRACT);               
	if (((p->A.value & 0xF) + (p->C.value & 0xF)) > 0xF)     
	  p->flag.setFlag(FlagRegister::HALFCARRY);
	if (val > 0xFF)                                          
	  p->flag.setFlag(FlagRegister::CARRY);

	p->A.value = (val & 0xFF);
}

void ADD_AD::exec(Processor *p)
{
  	auto val = p->A.value + p->D.value;
	if ((val & 0xFF) == 0)
	  p->flag.setFlag(FlagRegister::ZERO);                   
	p->flag.unsetFlag(FlagRegister::SUBTRACT);               
	if (((p->A.value & 0xF) + (p->D.value & 0xF)) > 0xF)     
	  p->flag.setFlag(FlagRegister::HALFCARRY);
	if (val > 0xFF)                                          
	  p->flag.setFlag(FlagRegister::CARRY);

	p->A.value = (val & 0xFF);
}

void ADD_AE::exec(Processor *p)
{
  	auto val = p->A.value + p->E.value;
	if ((val & 0xFF) == 0)
	  p->flag.setFlag(FlagRegister::ZERO);                   
	p->flag.unsetFlag(FlagRegister::SUBTRACT);               
	if (((p->A.value & 0xF) + (p->E.value & 0xF)) > 0xF)     
	  p->flag.setFlag(FlagRegister::HALFCARRY);
	if (val > 0xFF)                                          
	  p->flag.setFlag(FlagRegister::CARRY);

	p->A.value = (val & 0xFF);
}

void ADD_AH::exec(Processor *p)
{
  	auto val = p->A.value + p->H.value;
	if ((val & 0xFF) == 0)
	  p->flag.setFlag(FlagRegister::ZERO);                           
	p->flag.unsetFlag(FlagRegister::SUBTRACT);
	if (((p->A.value & 0xF) + (p->H.value & 0xF)) > 0xF)    
	  p->flag.setFlag(FlagRegister::HALFCARRY);
	if (val > 0xFF)                                         
	  p->flag.setFlag(FlagRegister::CARRY);

	p->A.value = (val & 0xFF);
}

void ADD_AL::exec(Processor *p)
{
  	auto val = p->A.value + p->L.value;
	if ((val & 0xFF) == 0)
	  p->flag.setFlag(FlagRegister::ZERO);
	p->flag.unsetFlag(FlagRegister::SUBTRACT);
	if (((p->A.value & 0xF) + (p->L.value & 0xF)) > 0xF)
	  p->flag.setFlag(FlagRegister::HALFCARRY);
	if (val > 0xFF)
	  p->flag.setFlag(FlagRegister::CARRY);

	p->A.value = (val & 0xFF);
}

void ADD_AHL::exec(Processor *p)
{
  	auto val = p->A.value + p->PC.value;
	if ((val & 0xFF) == 0)
	  p->flag.setFlag(FlagRegister::ZERO);
	p->flag.unsetFlag(FlagRegister::SUBTRACT);
	if (((p->A.value & 0xF) + (p->PC.value & 0xF)) > 0xF)
	  p->flag.setFlag(FlagRegister::HALFCARRY);
	if (val > 0xFF)
	  p->flag.setFlag(FlagRegister::CARRY);

	p->A.value = (val & 0xFF);
}

void ADD_AADDRESS::exec(Processor *p)
{
  p = p;
  /*auto mem = p._read(this->args[0]);
	auto val = p->A.value + mem;
	if ((val & 0xFF) == 0)
	  p->flag.setFlag(FlagRegister::ZERO);
	p->flag.unsetFlag(FlagRegister::SUBTRACT);
	if (((p->A.value & 0xF) + (p->PC.value & 0xF)) > 0xF)
	  p->flag.setFlag(FlagRegister::HALFCARRY);
	if (val > 0xFF)
	  p->flag.setFlag(FlagRegister::CARRY);

	  p->A.value = (val & 0xFF);*/
}    

//ADC instructions

