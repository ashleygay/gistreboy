#include <instructionargs.hpp>

// Helper functions to add correponding elements to a vector
void addShort(InstructionArgs& args, uint16_t val)
{
	args.push_back(val);
}

void addByte(InstructionArgs& args, uint8_t val)
{
	args.push_back(val);
}

void addRegRef(InstructionArgs& args, std::reference_wrapper<Register> reg)
{
	args.push_back(reg);
}

void addDRegRef(InstructionArgs& args, std::reference_wrapper<DRegister> reg)
{
	args.push_back(reg);
}
