#include <instructionargs.hpp>

// Helper functions to add correponding elements to a vector
void addUChar(InstructionArgs& args, int val)
{
	args.push_back((uint8_t)val);
}

void addShort(InstructionArgs& args, int val)
{
	args.push_back((uint16_t)val);
}

void addRegRef(InstructionArgs& args, std::reference_wrapper<Register> reg)
{
	args.push_back(reg);
}

void addDRegRef(InstructionArgs& args, std::reference_wrapper<DRegister> reg)
{
	args.push_back(reg);
}
