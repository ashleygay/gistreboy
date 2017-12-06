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
