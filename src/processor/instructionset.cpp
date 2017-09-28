#include <instructionset.hpp>

int InstructionSet::isInstructionValid(OpCode opCode)
{
	auto elt = map.find(opCode);
	return (elt != map.end());
}

int InstructionSet::addInstruction(Instruction* instr)
{
	auto elt = map.find(instr->opCode());
	if (elt == map.end())
		map[instr->opCode()] = instr;
	return (elt == map.end());
}
