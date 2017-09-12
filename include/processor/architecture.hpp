#pragma once

#include <unordered_map>

#include <instruction.hpp>
#include <opcode.hpp>
#include <boost/variant/recursive_variant.hpp>

using OpCodeToInstruction = std::unordered_map<OpCode, Instruction *>;
using Variant = boost::variant<Instruction *, OpCodeToInstruction>;
using OpCodeToVariant = std::unordered_map<OpCode, Variant>;

class Architecture
{
	public:
		Architecture()
		{
			//TODO: we add all instructions to the map here
		}


/*
	class NodeElement
	{
		Element elt;
	};
*/

	// 0 unknown instruction
	// 1 complete instruction
	// -1 partially correct
	int checkInstruction(OpCode opcode);

	private:
		OpCodeToVariant map;
};
