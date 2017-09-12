#include <architecture.hpp>

int Architecture::checkInstruction(OpCode opCode)
{
	auto elt = map.find(opCode);
	return (elt != map.end());
}

int Architecture::addInstruction(Instruction* instr)
{
	auto elt = map.find(instr->opCode());
	if (elt == map.end())
		map[instr->opCode()] = instr;
	return (elt == map.end());
}
