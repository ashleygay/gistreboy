#pragma once

#include <iostream>
#include <vector>

#include <debug.hpp>
#include <processor.hpp>
#include <instructionargs.hpp>
#include <registers.hpp>

class Instruction {
	public:
		virtual void exec(Processor *p) = 0;
		virtual const char *toStr() = 0;
		virtual uint16_t opCode() = 0;
		virtual int nbCycles() = 0;
		virtual int nbArgs() = 0;
		virtual void setArgs(InstructionArgs & args) = 0;
		virtual int argSize(int i) = 0;
};

/*
 * Argument of the instruction are stored in a std::vector<>.
 * Arguments are stored starting at 0, so if an instruction takes
 * only one argument, its argument will be at this->_args[0].
 */


#define decl_instruction(name, opc, nb_cycles, nb_args, size_arg0, size_arg1)\
	class name : public Instruction{\
		public:\
			virtual void exec(Processor *p);\
			virtual const char *toStr() { return #name; }\
			virtual uint16_t opCode() { return opc; } \
			virtual int nbCycles() { return nb_cycles; } \
			virtual int nbArgs() {return nb_args;}\
			virtual void setArgs(InstructionArgs &args) {_args = args;}\
			virtual int argSize(int i)\
				{return i ? size_arg1 : size_arg0;}\
		private:\
			InstructionArgs _args; \
	};

// LD INSTRUCTIONS

decl_instruction(LD_AX, 0x3E, 8, 1, 1, 0)
decl_instruction(LD_BX, 0x06, 8, 1, 1, 0)
decl_instruction(LD_CX, 0x0E, 8, 1, 1, 0)
decl_instruction(LD_DX, 0x16, 8, 1, 1, 0)
decl_instruction(LD_EX, 0x1E, 8, 1, 1, 0)
decl_instruction(LD_HX, 0x26, 8, 1, 1, 0)
decl_instruction(LD_LX, 0x2E, 8, 1, 1, 0)

decl_instruction(LD_AA, 0x7F, 4, 0, 0, 0)
decl_instruction(LD_AB, 0x78, 4, 0, 0, 0)
decl_instruction(LD_AC, 0x79, 4, 0, 0, 0)
decl_instruction(LD_AD, 0x7A, 4, 0, 0, 0)
decl_instruction(LD_AE, 0x7B, 4, 0, 0, 0)
decl_instruction(LD_AH, 0x7C, 4, 0, 0, 0)
decl_instruction(LD_AL, 0x7D, 4, 0, 0, 0)
decl_instruction(LD_AHL, 0x7E, 8, 0, 0, 0)
decl_instruction(LD_BA, 0x47, 4, 0, 0, 0)
decl_instruction(LD_BB, 0x40, 4, 0, 0, 0)
decl_instruction(LD_BC, 0x41, 4, 0, 0, 0)
decl_instruction(LD_BD, 0x42, 4, 0, 0, 0)
decl_instruction(LD_BE, 0x43, 4, 0, 0, 0)
decl_instruction(LD_BH, 0x44, 4, 0, 0, 0)
decl_instruction(LD_BL, 0x45, 4, 0, 0, 0)
decl_instruction(LD_BHL, 0x46, 8, 0, 0, 0)
decl_instruction(LD_CA, 0x4F, 4, 0, 0, 0)
decl_instruction(LD_CB, 0x48, 4, 0, 0, 0)
decl_instruction(LD_CC, 0x49, 4, 0, 0, 0)
decl_instruction(LD_CD, 0x4A, 4, 0, 0, 0)
decl_instruction(LD_CE, 0x4B, 4, 0, 0, 0)
decl_instruction(LD_CH, 0x4C, 4, 0, 0, 0)
decl_instruction(LD_CL, 0x4D, 4, 0, 0, 0)
decl_instruction(LD_CHL, 0x4E, 8, 0, 0, 0)
decl_instruction(LD_DA, 0x57, 4, 0, 0, 0)
decl_instruction(LD_DB, 0x50, 4, 0, 0, 0)
decl_instruction(LD_DC, 0x51, 4, 0, 0, 0)
decl_instruction(LD_DD, 0x52, 4, 0, 0, 0)
decl_instruction(LD_DE, 0x53, 4, 0, 0, 0)
decl_instruction(LD_DH, 0x54, 4, 0, 0, 0)
decl_instruction(LD_DL, 0x55, 4, 0, 0, 0)
decl_instruction(LD_DHL, 0x56, 8, 0, 0, 0)
decl_instruction(LD_EA, 0x5F, 4, 0, 0, 0)
decl_instruction(LD_EB, 0x58, 4, 0, 0, 0)
decl_instruction(LD_EC, 0x59, 4, 0, 0, 0)
decl_instruction(LD_ED, 0x5A, 4, 0, 0, 0)
decl_instruction(LD_EE, 0x5B, 4, 0, 0, 0)
decl_instruction(LD_EH, 0x5C, 4, 0, 0, 0)
decl_instruction(LD_EL, 0x5D, 4, 0, 0, 0)
decl_instruction(LD_EHL, 0x5E, 8, 0, 0, 0)
decl_instruction(LD_HA, 0x67, 4, 0, 0, 0)
decl_instruction(LD_HB, 0x60, 4, 0, 0, 0)
decl_instruction(LD_HC, 0x61, 4, 0, 0, 0)
decl_instruction(LD_HD, 0x62, 4, 0, 0, 0)
decl_instruction(LD_HE, 0x63, 4, 0, 0, 0)
decl_instruction(LD_HH, 0x64, 4, 0, 0, 0)
decl_instruction(LD_HL, 0x65, 4, 0, 0, 0)
decl_instruction(LD_HHL, 0x66, 8, 0, 0, 0)
decl_instruction(LD_LA, 0x6F, 4, 0, 0, 0)
decl_instruction(LD_LB, 0x68, 4, 0, 0, 0)
decl_instruction(LD_LC, 0x69, 4, 0, 0, 0)
decl_instruction(LD_LD, 0x6A, 4, 0, 0, 0)
decl_instruction(LD_LE, 0x6B, 4, 0, 0, 0)
decl_instruction(LD_LH, 0x6C, 4, 0, 0, 0)
decl_instruction(LD_LL, 0x6D, 4, 0, 0, 0)
decl_instruction(LD_LHL, 0x6E, 8, 0, 0, 0)
decl_instruction(LD_HLB, 0x70, 8, 0, 0, 0)
decl_instruction(LD_HLC, 0x71, 8, 0, 0, 0)
decl_instruction(LD_HLD, 0x72, 8, 0, 0, 0)
decl_instruction(LD_HLE, 0x73, 8, 0, 0, 0)
decl_instruction(LD_HLH, 0x74, 8, 0, 0, 0)
decl_instruction(LD_HLL, 0x75, 8, 0, 0, 0)
decl_instruction(LD_HLn, 0x36, 12, 1, 1, 0)

decl_instruction(LD_ABC, 0x0A, 8, 0, 0, 0)
decl_instruction(LD_BCA, 0x02, 8, 0, 0, 0)
decl_instruction(LD_ADE, 0x1A, 8, 0, 0, 0)
decl_instruction(LD_DEA, 0x12, 8, 0, 0, 0)
decl_instruction(LD_HLA, 0x77, 8, 0, 0, 0)
decl_instruction(LD_Ann, 0xFA, 16, 1, 2, 0)
decl_instruction(LD_nnA, 0xEA, 16, 1, 2, 0)

decl_instruction(LD_AC2, 0xF2, 8, 0, 0, 0)
decl_instruction(LD_C2A, 0xE2, 8, 0, 0, 0)

decl_instruction(LDD_AHL, 0x3A, 8, 0, 0, 0)
decl_instruction(LDD_HLA, 0x32, 8, 0, 0, 0)
decl_instruction(LDI_AHL, 0x2A, 8, 0, 0, 0)
decl_instruction(LDI_HLA, 0x22, 8, 0, 0, 0)
decl_instruction(LDH_nA, 0xE0, 12, 1, 1, 0)
decl_instruction(LDH_An, 0xF0, 12, 1, 1, 0)

decl_instruction(LD_BCnn, 0x01, 12, 1, 2, 0)
decl_instruction(LD_DEnn, 0x11, 12, 1, 2, 0)
decl_instruction(LD_HLnn, 0x21, 12, 1, 2, 0)
decl_instruction(LD_SPnn, 0x31, 12, 1, 2, 0)
decl_instruction(LD_nnSP, 0x08, 20, 1, 2, 0)
decl_instruction(LD_SPHL, 0xF9, 8, 0, 0, 0)
decl_instruction(LD_HLSPn, 0xF8, 12, 1, 1, 0)

decl_instruction(PUSH_BC, 0xC5, 16, 0, 0, 0)
decl_instruction(PUSH_DE, 0xD5, 16, 0, 0, 0)
decl_instruction(PUSH_HL, 0xE5, 16, 0, 0, 0)
decl_instruction(POP_BC, 0xC1, 12, 0, 0, 0)
decl_instruction(POP_DE, 0xD1, 12, 0, 0, 0)
decl_instruction(POP_HL, 0xE1, 12, 0, 0, 0)

// NOP INSTRUCTION

decl_instruction(NOP, 0x00, 4, 0, 0, 0)

// ADD INSTRUCTIONS

decl_instruction(ADD_AA, 0x87, 4, 2, 1, 1)
decl_instruction(ADD_AB, 0x80, 4, 2, 1, 1)
decl_instruction(ADD_AC, 0x81, 4, 2, 1, 1)
decl_instruction(ADD_AD, 0x82, 4, 2, 1, 1)  
decl_instruction(ADD_AE, 0x83, 4, 2, 1, 1)
decl_instruction(ADD_AH, 0x84, 4, 2, 1, 1)  
decl_instruction(ADD_AL, 0x85, 4, 2, 1, 1)
decl_instruction(ADD_AHL, 0x86, 8, 0, 0, 0)  
decl_instruction(ADD_Aaddress, 0xC6, 8, 1, 2, 0)

// ADC Instructions

decl_instruction(ADC_AA, 0x8F, 4, 2, 1, 1)
decl_instruction(ADC_AB, 0x88, 4, 2, 1, 1)
decl_instruction(ADC_AC, 0x89, 4, 2, 1, 1)
decl_instruction(ADC_AD, 0x8A, 4, 2, 1, 1)
decl_instruction(ADC_AE, 0x8B, 4, 2, 1, 1)
decl_instruction(ADC_AH, 0x8C, 4, 2, 1, 1)
decl_instruction(ADC_AL, 0x8D, 4, 2, 1, 1)
decl_instruction(ADC_AHL, 0x8E, 8, 0, 0, 0)
decl_instruction(ADC_Aaddress, 0xCE, 8, 1, 2, 0) 


// SUB Instructions

decl_instruction(SUB_AA, 0x97, 4, 0, 0, 0)
decl_instruction(SUB_AB, 0x90, 4, 0, 0, 0)
decl_instruction(SUB_AC, 0x91, 4, 0, 0, 0)
decl_instruction(SUB_AD, 0x92, 4, 0, 0, 0)
decl_instruction(SUB_AE, 0x93, 4, 0, 0, 0)
decl_instruction(SUB_AH, 0x94, 4, 0, 0, 0)
decl_instruction(SUB_AL, 0x95, 4, 0, 0, 0)
decl_instruction(SUB_AHL, 0x96, 8, 0, 0, 0)
decl_instruction(SUB_Aaddress, 0xD6, 8, 1, 2, 0)  

// SBC Instructions

decl_instruction(SBC_AA, 0x9F, 4, 2, 1, 1)
decl_instruction(SBC_AB, 0x98, 4, 2, 1, 1)
decl_instruction(SBC_AC, 0x99, 4, 2, 1, 1)
decl_instruction(SBC_AD, 0x9A, 4, 2, 1, 1)
decl_instruction(SBC_AE, 0x9B, 4, 2, 1, 1)
decl_instruction(SBC_AH, 0x9C, 4, 2, 1, 1)
decl_instruction(SBC_AL, 0x9D, 4, 2, 1, 1)
decl_instruction(SBC_AHL, 0x9E, 8, 0, 0, 0)
decl_instruction(SBC_Aaddress, 0xDE, 8, 1, 2, 1) //pas d'opcode in manual

// AND Instructions

decl_instruction(AND_AA, 0xA7, 4, 2, 1, 1)
decl_instruction(AND_AB, 0xA0, 4, 2, 1, 1)
decl_instruction(AND_AC, 0xA1, 4, 2, 1, 1)
decl_instruction(AND_AD, 0xA2, 4, 2, 1, 1)
decl_instruction(AND_AE, 0xA3, 4, 2, 1, 1)
decl_instruction(AND_AH, 0xA4, 4, 2, 1, 1)
decl_instruction(AND_AL, 0xA5, 4, 2, 1, 1)
decl_instruction(AND_AHL, 0xA6, 8, 0, 0, 0)
decl_instruction(AND_Aaddress, 0xE6, 8, 1, 2, 0)  

// OR Instructions

decl_instruction(OR_AA, 0xB7, 4, 2, 1, 1)
decl_instruction(OR_AB, 0xB0, 4, 2, 1, 1)
decl_instruction(OR_AC, 0xB1, 4, 2, 1, 1)
decl_instruction(OR_AD, 0xB2, 4, 2, 1, 1)
decl_instruction(OR_AE, 0xB3, 4, 2, 1, 1)
decl_instruction(OR_AH, 0xB4, 4, 2, 1, 1)
decl_instruction(OR_AL, 0xB5, 4, 2, 1, 1)
decl_instruction(OR_AHL, 0xB6, 8, 0, 0, 0)
decl_instruction(OR_Aaddress, 0xF6, 8, 1, 2, 0)

// XOR Instructions

decl_instruction(XOR_AA, 0xAF, 4, 2, 1, 1)
decl_instruction(XOR_AB, 0xA8, 4, 2, 1, 1)
decl_instruction(XOR_AC, 0xA9, 4, 2, 1, 1)
decl_instruction(XOR_AD, 0xAA, 4, 2, 1, 1)
decl_instruction(XOR_AE, 0xAB, 4, 2, 1, 1)
decl_instruction(XOR_AH, 0xAC, 4, 2, 1, 1)
decl_instruction(XOR_AL, 0xAD, 4, 2, 1, 1)
decl_instruction(XOR_AHL, 0xAE, 8, 0, 0, 0)
decl_instruction(XOR_Aaddress, 0xEE, 8, 1, 2, 0)  

// CP Instructions

decl_instruction(CP_AA, 0xBF, 4, 2, 1, 1)
decl_instruction(CP_AB, 0xB8, 4, 2, 1, 1)
decl_instruction(CP_AC, 0xB9, 4, 2, 1, 1)
decl_instruction(CP_AD, 0xBA, 4, 2, 1, 1)
decl_instruction(CP_AE, 0xBB, 4, 2, 1, 1)
decl_instruction(CP_AH, 0xBC, 4, 2, 1, 1)
decl_instruction(CP_AL, 0xBD, 4, 2, 1, 1)
decl_instruction(CP_AHL, 0xBE, 8, 0, 0, 0)
decl_instruction(CP_Aaddress, 0xFE, 8, 1, 2, 0) 


// INC Instructions

decl_instruction(INC_AX, 0x3C, 4, 1, 1, 0)
decl_instruction(INC_BX, 0x04, 4, 1, 1, 0)
decl_instruction(INC_CX, 0x0C, 4, 1, 1, 0)
decl_instruction(INC_DX, 0x14, 4, 1, 1, 0)
decl_instruction(INC_EX, 0x1C, 4, 1, 1, 0)
decl_instruction(INC_HX, 0x24, 4, 1, 1, 0)
decl_instruction(INC_LX, 0x2C, 4, 1, 1, 0)
//decl_instruction(INC_HLX, 0x34, 12, 1, 1, 0)

// DEC Instructions

decl_instruction(DEC_AX, 0x3D, 4, 1, 1, 0)
decl_instruction(DEC_BX, 0x05, 4, 1, 1, 0)
decl_instruction(DEC_CX, 0x0D, 4, 1, 1, 0)
decl_instruction(DEC_DX, 0x15, 4, 1, 1, 0)
decl_instruction(DEC_EX, 0x1D, 4, 1, 1, 0)
decl_instruction(DEC_HX, 0x25, 4, 1, 1, 0)
decl_instruction(DEC_LX, 0x2D, 4, 1, 1, 0)
//decl_instruction(DEC_HLX, 0x35, 12, 1, 1, 0)  

// SWAP Instructions

decl_instruction(SWAP_AX, 0xCB37, 8, 1, 1, 0)
decl_instruction(SWAP_BX, 0xCB30, 8, 1, 1, 0)
decl_instruction(SWAP_CX, 0xCB31, 8, 1, 1, 0)
decl_instruction(SWAP_DX, 0xCB32, 8, 1, 1, 0)
decl_instruction(SWAP_EX, 0xCB33, 8, 1, 1, 0)
decl_instruction(SWAP_HX, 0xCB34, 8, 1, 1, 0)
decl_instruction(SWAP_LX, 0xCB35, 8, 1, 1, 0)
//decl_instruction(SWAP_HLX, 0xCB36, 16, 1, 1, 0) 

decl_instruction(DAA, 0x27, 4, 0, 0, 0)
decl_instruction(CPL, 0x2F, 4, 0, 0, 0)
decl_instruction(CCF, 0x3F, 4, 0, 0, 0)
decl_instruction(SCF, 0x37, 4, 0, 0, 0)


// BIT Instructions

/*decl_instruction(BIT_BA, 0xCB47, 8, 2, 1, 1)
decl_instruction(BIT_BB, 0xCB40, 8, 2, 1, 1)
decl_instruction(BIT_BC, 0xCB41, 8, 2, 1, 1)
decl_instruction(BIT_BD, 0xCB42, 8, 2, 1, 1)
decl_instruction(BIT_BE, 0xCB43, 8, 2, 1, 1)
decl_instruction(BIT_BH, 0xCB44, 8, 2, 1, 1)
decl_instruction(BIT_BL, 0xCB45, 8, 2, 1, 1)
//decl_instruction(SWAP_HLX, 0xCB36, 16, 1, 1, 0)*/

// RRC Instructions

decl_instruction(RRC_AX, 0xCB0F, 8, 1, 1, 0)                                                           
decl_instruction(RRC_BX, 0xCB08, 8, 1, 1, 0)
decl_instruction(RRC_CX, 0xCB09, 8, 1, 1, 0)
decl_instruction(RRC_DX, 0xCB0A, 8, 1, 1, 0)
decl_instruction(RRC_EX, 0xCB0B, 8, 1, 1, 0)
decl_instruction(RRC_HX, 0xCB0C, 8, 1, 1, 0)
decl_instruction(RRC_LX, 0xCB0D, 8, 1, 1, 0)
//decl_instruction(RRC_HLX, 0xCB0E, 16, 1, 2, 0) 

// RLC Instructions

decl_instruction(RLC_AX, 0xCB07, 8, 1, 1, 0)
decl_instruction(RLC_BX, 0xCB00, 8, 1, 1, 0)
decl_instruction(RLC_CX, 0xCB01, 8, 1, 1, 0)
decl_instruction(RLC_DX, 0xCB02, 8, 1, 1, 0)
decl_instruction(RLC_EX, 0xCB03, 8, 1, 1, 0)
decl_instruction(RLC_HX, 0xCB04, 8, 1, 1, 0)
decl_instruction(RLC_LX, 0xCB05, 8, 1, 1, 0)
//decl_instruction(RLC_HLX, 0xCB06, 16, 1, 2, 0)   

// RL Instructions

decl_instruction(RL_AX, 0xCB17, 8, 1, 1, 0)
decl_instruction(RL_BX, 0xCB10, 8, 1, 1, 0)
decl_instruction(RL_CX, 0xCB11, 8, 1, 1, 0)
decl_instruction(RL_DX, 0xCB12, 8, 1, 1, 0)
decl_instruction(RL_EX, 0xCB13, 8, 1, 1, 0)
decl_instruction(RL_HX, 0xCB14, 8, 1, 1, 0)
decl_instruction(RL_LX, 0xCB15, 8, 1, 1, 0)
//decl_instruction(RLC_HLX, 0xCB16, 16, 1, 2, 0)

// RR Instructions

decl_instruction(RR_AX, 0xCB1F, 8, 1, 1, 0)
decl_instruction(RR_BX, 0xCB18, 8, 1, 1, 0)
decl_instruction(RR_CX, 0xCB19, 8, 1, 1, 0)
decl_instruction(RR_DX, 0xCB1A, 8, 1, 1, 0)
decl_instruction(RR_EX, 0xCB1B, 8, 1, 1, 0)
decl_instruction(RR_HX, 0xCB1C, 8, 1, 1, 0)
decl_instruction(RR_LX, 0xCB1D, 8, 1, 1, 0)
//decl_instruction(RLC_HLX, 0xCB1E, 16, 1, 2, 0) 


// SLA Instructions

decl_instruction(SLA_AX, 0xCB27, 8, 1, 1, 0)
decl_instruction(SLA_BX, 0xCB20, 8, 1, 1, 0)
decl_instruction(SLA_CX, 0xCB21, 8, 1, 1, 0)
decl_instruction(SLA_DX, 0xCB22, 8, 1, 1, 0)
decl_instruction(SLA_EX, 0xCB23, 8, 1, 1, 0)
decl_instruction(SLA_HX, 0xCB24, 8, 1, 1, 0)
decl_instruction(SLA_LX, 0xCB25, 8, 1, 1, 0)
//decl_instruction(SLA_HLX, 0xCB26, 16, 1, 2, 0)

// SRA Instructions

decl_instruction(SRA_AX, 0xCB2F, 8, 1, 1, 0)
decl_instruction(SRA_BX, 0xCB28, 8, 1, 1, 0)
decl_instruction(SRA_CX, 0xCB29, 8, 1, 1, 0)
decl_instruction(SRA_DX, 0xCB2A, 8, 1, 1, 0)
decl_instruction(SRA_EX, 0xCB2B, 8, 1, 1, 0)
decl_instruction(SRA_HX, 0xCB2C, 8, 1, 1, 0)
decl_instruction(SRA_LX, 0xCB2D, 8, 1, 1, 0)
//decl_instruction(SRA_HLX, 0xCB2E, 16, 1, 2, 0)

// SRL Instructions

decl_instruction(SRL_AX, 0xCB3F, 8, 1, 1, 0)
decl_instruction(SRL_BX, 0xCB38, 8, 1, 1, 0)
decl_instruction(SRL_CX, 0xCB39, 8, 1, 1, 0)
decl_instruction(SRL_DX, 0xCB3A, 8, 1, 1, 0)
decl_instruction(SRL_EX, 0xCB3B, 8, 1, 1, 0)
decl_instruction(SRL_HX, 0xCB3C, 8, 1, 1, 0)
decl_instruction(SRL_LX, 0xCB3D, 8, 1, 1, 0)
//decl_instruction(SRL_HLX, 0xCB3E, 16, 1, 2, 0) 


decl_instruction(JP, 0xC3, 12, 1, 2, 0)
decl_instruction(JPNZ, 0xC2, 12, 1, 2, 0)
decl_instruction(JPZ, 0xCA, 12, 1, 2, 0)
decl_instruction(JPNC, 0xD2, 12, 1, 2, 0)
decl_instruction(JPC, 0xDA, 12, 1, 2, 0)
decl_instruction(JPHL, 0xE9, 12, 0, 0, 0)
decl_instruction(JR, 0x18, 8, 1, 1, 0)
decl_instruction(JRNZ, 0x20, 8, 1, 1, 0)
decl_instruction(JRZ, 0x28, 8, 1, 1, 0)
decl_instruction(JRNC, 0x30, 8, 1, 1, 0)
decl_instruction(JRC, 0x38, 8, 1, 1, 0)

decl_instruction(CALL, 0xCD, 12, 1, 2, 0)
decl_instruction(CALLNZ, 0xC4, 12, 1, 2, 0)
decl_instruction(CALLZ, 0xCC, 12, 1, 2, 0)
decl_instruction(CALLNC, 0xD4, 12, 1, 2, 0)
decl_instruction(CALLC, 0xDC, 12, 1, 2, 0)
