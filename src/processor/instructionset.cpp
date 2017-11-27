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
	add_instr(LD_AHL)

	add_instr(LD_BA)
	add_instr(LD_BB)
	add_instr(LD_BC)
	add_instr(LD_BD)
	add_instr(LD_BE)
	add_instr(LD_BL)
	add_instr(LD_BHL)

	add_instr(LD_CA)
	add_instr(LD_CB)
	add_instr(LD_CC)
	add_instr(LD_CD)
	add_instr(LD_CE)
	add_instr(LD_CL)
	add_instr(LD_CHL)

	add_instr(LD_DA)
	add_instr(LD_DB)
	add_instr(LD_DC)
	add_instr(LD_DD)
	add_instr(LD_DE)
	add_instr(LD_DL)
	add_instr(LD_DHL)

	add_instr(LD_EA)
	add_instr(LD_EB)
	add_instr(LD_EC)
	add_instr(LD_ED)
	add_instr(LD_EE)
	add_instr(LD_EL)
	add_instr(LD_EHL)

	add_instr(LD_LA)
	add_instr(LD_LB)
	add_instr(LD_LC)
	add_instr(LD_LD)
	add_instr(LD_LE)
	add_instr(LD_LL)
	add_instr(LD_LHL)

	add_instr(LD_HLB)
	add_instr(LD_HLC)
	add_instr(LD_HLD)
	add_instr(LD_HLE)
	add_instr(LD_HLH)
	add_instr(LD_HLL)
	add_instr(LD_HLn)

	add_instr(LD_ABC)
	add_instr(LD_BCA)
	add_instr(LD_ADE)
	add_instr(LD_DEA)
	add_instr(LD_HLA)
	add_instr(LD_Ann)
	add_instr(LD_nnA)

	add_instr(LD_AC2)
	add_instr(LD_C2A)

	add_instr(LDD_AHL)
	add_instr(LDD_HLA)
	add_instr(LDI_AHL)
	add_instr(LDI_HLA)
	add_instr(LDH_nA)
	add_instr(LDH_An)

	add_instr(LD_BCnn)
	add_instr(LD_DEnn)
	add_instr(LD_HLnn)
	add_instr(LD_SPnn)
	add_instr(LD_nnSP)
	add_instr(LD_SPHL)
	add_instr(LD_HLSPn)

	add_instr(PUSH_BC)
	add_instr(PUSH_DE)
	add_instr(PUSH_HL)
	add_instr(POP_BC)
	add_instr(POP_DE)
	add_instr(POP_HL)


	add_instr(ADD_AA)
	add_instr(ADD_AB)
	add_instr(ADD_AC)
	add_instr(ADD_AD)
	add_instr(ADD_AE)
	add_instr(ADD_AH)
	add_instr(ADD_AL)
	add_instr(ADD_AHL)
	add_instr(ADD_Aaddress)


	add_instr(ADC_AA)
	add_instr(ADC_AB)
	add_instr(ADC_AC)
	add_instr(ADC_AD)
	add_instr(ADC_AE)
	add_instr(ADC_AH)
	add_instr(ADC_AL)
	add_instr(ADC_AHL)
	add_instr(ADC_Aaddress)


	add_instr(SUB_AA)
	add_instr(SUB_AB)
	add_instr(SUB_AC)
	add_instr(SUB_AD)
	add_instr(SUB_AE)
	add_instr(SUB_AH)
	add_instr(SUB_AL)
	add_instr(SUB_AHL)
	add_instr(SUB_Aaddress) 

	add_instr(SBC_AA)
	add_instr(SBC_AB)
	add_instr(SBC_AC)
        add_instr(SBC_AD)
	add_instr(SBC_AE)
	add_instr(SBC_AH)
	add_instr(SBC_AL)
	add_instr(SBC_AHL)
	add_instr(SBC_Aaddress) 

	add_instr(AND_AA)
	add_instr(AND_AB)
	add_instr(AND_AC)
	add_instr(AND_AD)
	add_instr(AND_AE)
	add_instr(AND_AH)
	add_instr(AND_AL)
	add_instr(AND_AHL)
	add_instr(AND_Aaddress) 

	add_instr(OR_AA)
	add_instr(OR_AB)
	add_instr(OR_AC)
	add_instr(OR_AD)
	add_instr(OR_AE)
	add_instr(OR_AH)
	add_instr(OR_AL)
	add_instr(OR_AHL)
	add_instr(OR_Aaddress)

	add_instr(XOR_AA)
	add_instr(XOR_AB)
	add_instr(XOR_AC)
	add_instr(XOR_AD)
	add_instr(XOR_AE)
	add_instr(XOR_AH)
	add_instr(XOR_AL)
	add_instr(XOR_AHL)
	add_instr(XOR_Aaddress)


	add_instr(CP_AA)
	add_instr(CP_AB)
	add_instr(CP_AC)
	add_instr(CP_AD)
	add_instr(CP_AE)
	add_instr(CP_AH)
	add_instr(CP_AL)
	add_instr(CP_AHL)
	add_instr(CP_Aaddress) 

	add_instr(INC_AX)
	add_instr(INC_BX)
	add_instr(INC_CX)
	add_instr(INC_DX)
	add_instr(INC_EX)
	add_instr(INC_HX)
	add_instr(INC_LX)
	  //add_instr(INC_HLX)


	add_instr(DEC_AX)
	add_instr(DEC_BX)
	add_instr(DEC_CX)
	add_instr(DEC_DX)
	add_instr(DEC_EX)
	add_instr(DEC_HX)
	add_instr(DEC_LX)
	  //add_instr(DEC_HLX)

	add_instr(SWAP_AX)
	add_instr(SWAP_BX)
	add_instr(SWAP_CX)
	add_instr(SWAP_DX)
	add_instr(SWAP_EX)
	add_instr(SWAP_HX)
	add_instr(SWAP_LX)
	  //add_instr(SWAP_HLX)

	add_instr(DAA)  
	add_instr(CPL)
	add_instr(CCF)
	add_instr(SCF)


	  /*add_instr(BIT_BA)
	add_instr(BIT_BB)
	add_instr(BIT_BC)
	add_instr(BIT_BD)
	add_instr(BIT_BE)
	add_instr(BIT_BH)
	add_instr(BIT_BL)
	//add_instr(SWAP_HLX)*/


	add_instr(RRC_AX)
	add_instr(RRC_BX)
	add_instr(RRC_CX)
	add_instr(RRC_DX)
	add_instr(RRC_EX)
	add_instr(RRC_HX)
	add_instr(RRC_LX)
	  //add_instr(RRC_HLX)

	add_instr(RLC_AX)
	add_instr(RLC_BX)
	add_instr(RLC_CX)
	add_instr(RLC_DX)
	add_instr(RLC_EX)
	add_instr(RLC_HX)
	add_instr(RLC_LX)
	  //add_instr(RLC_HLX)  

	add_instr(RL_AX)
	add_instr(RL_BX)
	add_instr(RL_CX)
	add_instr(RL_DX)
	add_instr(RL_EX)
	add_instr(RL_HX)
	add_instr(RL_LX)
	//add_instr(RLC_HLX)

	add_instr(RR_AX)
	add_instr(RR_BX)
	add_instr(RR_CX)
	add_instr(RR_DX)
	add_instr(RR_EX)
	add_instr(RR_HX)
	add_instr(RR_LX)
	//add_instr(RLC_HLX) 

	add_instr(SLA_AX)
	add_instr(SLA_BX)
	add_instr(SLA_CX)
	add_instr(SLA_DX)
	add_instr(SLA_EX)
	add_instr(SLA_HX)
	add_instr(SLA_LX)
	//add_instr(SLA_HLX)  

	add_instr(SRA_AX)
	add_instr(SRA_BX)
	add_instr(SRA_CX)
	add_instr(SRA_DX)
	add_instr(SRA_EX)
	add_instr(SRA_HX)
	add_instr(SRA_LX)
	//add_instr(SRA_HLX) 


	add_instr(SRL_AX)
	add_instr(SRL_BX)
	add_instr(SRL_CX)
	add_instr(SRL_DX)
	add_instr(SRL_EX)
	add_instr(SRL_HX)
	add_instr(SRL_LX)
	//add_instr(SRL_HLX) 
	

	add_instr(JP)
	add_instr(JPNZ)
	add_instr(JPZ)
	add_instr(JPNC)
	add_instr(JPC)
	add_instr(JPHL)
	add_instr(JR)
	add_instr(JRNZ)
	add_instr(JRZ)
	add_instr(JRNC)
	add_instr(JRC)

	add_instr(CALL)
	add_instr(CALLNZ)
	add_instr(CALLZ)
	add_instr(CALLNC)
	add_instr(CALLC)
	
	add_instr(RST_0x00)
	add_instr(RST_0x08)
	add_instr(RST_0x10)
	add_instr(RST_0x18)
	add_instr(RST_0x20)
	add_instr(RST_0x28)
	add_instr(RST_0x30)
	add_instr(RST_0x38)

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
