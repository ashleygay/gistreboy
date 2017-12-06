#include <instructionargs.hpp>

// Helper functions to add correponding elements to a vector
void addShort(InstructionArg& arg, uint16_t val)
{
	arg.push_back(val);
}

void addByte(InstructionArg& arg, uint8_t val)
{
	arg.push_back(val);
}
