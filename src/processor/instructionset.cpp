#include <instructionset.hpp>
#include <instruction.hpp>
	

InstructionSet::InstructionSet()
{
	//TODO: we add all instructions to the map here
	//Use xmacros to generate all the instructions here
	/*	
	map = {
		#define X(instruction) \
			auto instr_##instruction = new instruction();\
			{instr_##instruction->getOpCode(), &instr_##instruction},
		#undef X
	};
	*/

	#define add_instr(instruct) \
		auto instr_##instruct = new instruct();\
		map[instr_##instruct->opCode()] = instr_##instruct;

	add_instr(NOP)


	add_instr(LD_BX)
	add_instr(LD_CX)
	add_instr(LD_DX)
	add_instr(LD_EX)
	add_instr(LD_HX)
	add_instr(LD_LX)

	add_instr(LD_AA)
	add_instr(LD_AB)
	add_instr(LD_AC)
	add_instr(LD_AD)
	add_instr(LD_AE)
	add_instr(LD_AL)

	add_instr(LD_BA)
	add_instr(LD_BB)
	add_instr(LD_BC)
	add_instr(LD_BD)
	add_instr(LD_BE)
	add_instr(LD_BL)

	add_instr(LD_CA)
	add_instr(LD_CB)
	add_instr(LD_CC)
	add_instr(LD_CD)
	add_instr(LD_CE)
	add_instr(LD_CL)

	add_instr(LD_DA)
	add_instr(LD_DB)
	add_instr(LD_DC)
	add_instr(LD_DD)
	add_instr(LD_DE)
	add_instr(LD_DL)

	add_instr(LD_EA)
	add_instr(LD_EB)
	add_instr(LD_EC)
	add_instr(LD_ED)
	add_instr(LD_EE)
	add_instr(LD_EL)

	add_instr(LD_AA)
	add_instr(LD_AB)
	add_instr(LD_AC)
	add_instr(LD_AD)
	add_instr(LD_AE)
	add_instr(LD_AL)

	#undef add_instr
}

int InstructionSet::isValidOpCode(OpCode opCode)
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


Instruction * InstructionSet::getInstruction(OpCode opCode)
{
	return map.find(opCode)->second;
}
