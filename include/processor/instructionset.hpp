#pragma once

#include <unordered_map>

#include <instruction.hpp>
#include <opcode.hpp>
#include <boost/variant/recursive_variant.hpp>

using OpCodeToInstruction = std::unordered_map<OpCode, Instruction *>;

class InstructionSet
{
	public:
		InstructionSet()
		{
			//TODO: we add all instructions to the map here
			//Use xmacros to generate all the instructions here
		/*	
			map = {
				#define X(instruction) \
					instruction::opCode, new instruction()
				#undef X
			}
		*/
		}


	// -1 invalid instruction
	// otherwise, the number of arguments it takes
	int isInstructionValid(OpCode opCode);

	int addInstruction(Instruction* instr);

	private:
		OpCodeToInstruction map;
};
