#pragma once

#include <unordered_map>

class Instruction;

#include <opcode.hpp>

using OpCodeToInstruction = std::unordered_map<OpCode, Instruction *>;

class InstructionSet
{
	public:
		InstructionSet();

		// -1 invalid instruction
		// otherwise, the number of arguments it takes
		int isValidOpCode(OpCode opCode);

		int addInstruction(Instruction* instr);

		// Function not safe on its own, use isOpCodeValid() first
		Instruction * getInstruction(OpCode opCode);

	private:
		OpCodeToInstruction map;
};
