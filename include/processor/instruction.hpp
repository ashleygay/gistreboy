#pragma once

#include <iostream>
#include <vector>

#include <debug.hpp>
#include <processor.hpp>
#include <instructionargs.hpp>
#include <registers.hpp>
#include <word_operations.hpp>

class Instruction {
	public:
		virtual void exec(Processor *p) = 0;
		virtual const char *toStr() = 0;
		virtual uint16_t opCode() = 0;
		virtual int nbCycles() = 0;
		virtual bool hasArg() = 0;
		virtual void setArg(InstructionArg & args) = 0;
		virtual int argSize() = 0;
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
			virtual bool hasArg() {return (nb_args == 1);}\
			virtual void setArg(InstructionArg &arg) {_arg = arg;}\
			virtual int argSize()\
				{return size_arg0;}\
		private:\
			InstructionArg _arg; \
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
decl_instruction(PUSH_AF, 0xF5, 16, 0, 0, 0)
decl_instruction(POP_BC, 0xC1, 12, 0, 0, 0)
decl_instruction(POP_DE, 0xD1, 12, 0, 0, 0)
decl_instruction(POP_HL, 0xE1, 12, 0, 0, 0)
decl_instruction(POP_AF, 0xF1, 12, 0, 0, 0)

// NOP INSTRUCTION

decl_instruction(NOP, 0x00, 4, 0, 0, 0)

// ADD INSTRUCTIONS

decl_instruction(ADD_AA, 0x87, 4, 0, 0, 0)
decl_instruction(ADD_AB, 0x80, 4, 0, 0, 0)
decl_instruction(ADD_AC, 0x81, 4, 0, 0, 0)
decl_instruction(ADD_AD, 0x82, 4, 0, 0, 0)  
decl_instruction(ADD_AE, 0x83, 4, 0, 0, 0)
decl_instruction(ADD_AH, 0x84, 4, 0, 0, 0)  
decl_instruction(ADD_AL, 0x85, 4, 0, 0, 0)
decl_instruction(ADD_AHL, 0x86, 8, 0, 0, 0)  
decl_instruction(ADD_AX, 0xC6, 8, 1, 1, 0)

decl_instruction(ADD_HLBC, 0x09, 8, 0, 0, 0)
decl_instruction(ADD_HLDE, 0x19, 8, 0, 0, 0)
decl_instruction(ADD_HLHL, 0x29, 8, 0, 0, 0)
decl_instruction(ADD_HLSP, 0x39, 8, 0, 0, 0)

decl_instruction(ADD_SPX, 0xE8, 16, 1, 1, 0)

// ADC Instructions

decl_instruction(ADC_AA, 0x8F, 4, 0, 0, 0)
decl_instruction(ADC_AB, 0x88, 4, 0, 0, 0)
decl_instruction(ADC_AC, 0x89, 4, 0, 0, 0)
decl_instruction(ADC_AD, 0x8A, 4, 0, 0, 0)
decl_instruction(ADC_AE, 0x8B, 4, 0, 0, 0)
decl_instruction(ADC_AH, 0x8C, 4, 0, 0, 0)
decl_instruction(ADC_AL, 0x8D, 4, 0, 0, 0)
decl_instruction(ADC_AHL, 0x8E, 8, 0, 0, 0)
decl_instruction(ADC_AX, 0xCE, 8, 1, 1, 0) 


// SUB Instructions

decl_instruction(SUB_AA, 0x97, 4, 0, 0, 0)
decl_instruction(SUB_AB, 0x90, 4, 0, 0, 0)
decl_instruction(SUB_AC, 0x91, 4, 0, 0, 0)
decl_instruction(SUB_AD, 0x92, 4, 0, 0, 0)
decl_instruction(SUB_AE, 0x93, 4, 0, 0, 0)
decl_instruction(SUB_AH, 0x94, 4, 0, 0, 0)
decl_instruction(SUB_AL, 0x95, 4, 0, 0, 0)
decl_instruction(SUB_AHL, 0x96, 8, 0, 0, 0)
decl_instruction(SUB_AX, 0xD6, 8, 1, 1, 0)  

// SBC Instructions

decl_instruction(SBC_AA, 0x9F, 4, 0, 0, 0)
decl_instruction(SBC_AB, 0x98, 4, 0, 0, 0)
decl_instruction(SBC_AC, 0x99, 4, 0, 0, 0)
decl_instruction(SBC_AD, 0x9A, 4, 0, 0, 0)
decl_instruction(SBC_AE, 0x9B, 4, 0, 0, 0)
decl_instruction(SBC_AH, 0x9C, 4, 0, 0, 0)
decl_instruction(SBC_AL, 0x9D, 4, 0, 0, 0)
decl_instruction(SBC_AHL, 0x9E, 8, 0, 0, 0)
decl_instruction(SBC_AX, 0xDE, 8, 1, 1, 0) //pas d'opcode in manual

// AND Instructions

decl_instruction(AND_AA, 0xA7, 4, 0, 0, 0)
decl_instruction(AND_AB, 0xA0, 4, 0, 0, 0)
decl_instruction(AND_AC, 0xA1, 4, 0, 0, 0)
decl_instruction(AND_AD, 0xA2, 4, 0, 0, 0)
decl_instruction(AND_AE, 0xA3, 4, 0, 0, 0)
decl_instruction(AND_AH, 0xA4, 4, 0, 0, 0)
decl_instruction(AND_AL, 0xA5, 4, 0, 0, 0)
decl_instruction(AND_AHL, 0xA6, 8, 0, 0, 0)
decl_instruction(AND_AX, 0xE6, 8, 1, 1, 0)  

// OR Instructions

decl_instruction(OR_AA, 0xB7, 4, 0, 0, 0)
decl_instruction(OR_AB, 0xB0, 4, 0, 0, 0)
decl_instruction(OR_AC, 0xB1, 4, 0, 0, 0)
decl_instruction(OR_AD, 0xB2, 4, 0, 0, 0)
decl_instruction(OR_AE, 0xB3, 4, 0, 0, 0)
decl_instruction(OR_AH, 0xB4, 4, 0, 0, 0)
decl_instruction(OR_AL, 0xB5, 4, 0, 0, 0)
decl_instruction(OR_AHL, 0xB6, 8, 0, 0, 0)
decl_instruction(OR_AX, 0xF6, 8, 1, 1, 0)

// XOR Instructions

decl_instruction(XOR_AA, 0xAF, 4, 0, 0, 0)
decl_instruction(XOR_AB, 0xA8, 4, 0, 0, 0)
decl_instruction(XOR_AC, 0xA9, 4, 0, 0, 0)
decl_instruction(XOR_AD, 0xAA, 4, 0, 0, 0)
decl_instruction(XOR_AE, 0xAB, 4, 0, 0, 0)
decl_instruction(XOR_AH, 0xAC, 4, 0, 0, 0)
decl_instruction(XOR_AL, 0xAD, 4, 0, 0, 0)
decl_instruction(XOR_AHL, 0xAE, 8, 0, 0, 0)
decl_instruction(XOR_AX, 0xEE, 8, 1, 1, 0)  

// CP Instructions

decl_instruction(CP_AA, 0xBF, 4, 0, 0, 0)
decl_instruction(CP_AB, 0xB8, 4, 0, 0, 0)
decl_instruction(CP_AC, 0xB9, 4, 0, 0, 0)
decl_instruction(CP_AD, 0xBA, 4, 0, 0, 0)
decl_instruction(CP_AE, 0xBB, 4, 0, 0, 0)
decl_instruction(CP_AH, 0xBC, 4, 0, 0, 0)
decl_instruction(CP_AL, 0xBD, 4, 0, 0, 0)
decl_instruction(CP_AHL, 0xBE, 8, 0, 0, 0)
decl_instruction(CP_AX, 0xFE, 8, 1, 1, 0) 


// INC Instructions

decl_instruction(INC_A, 0x3C, 4, 0, 0, 0)
decl_instruction(INC_B, 0x04, 4, 0, 0, 0)
decl_instruction(INC_C, 0x0C, 4, 0, 0, 0)
decl_instruction(INC_D, 0x14, 4, 0, 0, 0)
decl_instruction(INC_E, 0x1C, 4, 0, 0, 0)
decl_instruction(INC_H, 0x24, 4, 0, 0, 0)
decl_instruction(INC_L, 0x2C, 4, 0, 0, 0)

decl_instruction(INC_HLdereference, 0x34, 12, 1, 1, 0)


// INC on double registers
decl_instruction(INC_BC, 0x03, 8, 0, 0, 0)
decl_instruction(INC_DE, 0x13, 8, 0, 0, 0)
decl_instruction(INC_HL, 0x23, 8, 0, 0, 0)
decl_instruction(INC_SP, 0x33, 8, 0, 0, 0)

// DEC Instructions

decl_instruction(DEC_A, 0x3D, 4, 0, 0, 0)
decl_instruction(DEC_B, 0x05, 4, 0, 0, 0)
decl_instruction(DEC_C, 0x0D, 4, 0, 0, 0)
decl_instruction(DEC_D, 0x15, 4, 0, 0, 0)
decl_instruction(DEC_E, 0x1D, 4, 0, 0, 0)
decl_instruction(DEC_H, 0x25, 4, 0, 0, 0)
decl_instruction(DEC_L, 0x2D, 4, 0, 0, 0)

decl_instruction(DEC_HLdereference, 0x35, 12, 0, 0, 0)  
// DEC on double registers
decl_instruction(DEC_BC, 0x0B, 8, 0, 0, 0)
decl_instruction(DEC_DE, 0x1B, 8, 0, 0, 0)
decl_instruction(DEC_HL, 0x2B, 8, 0, 0, 0)
decl_instruction(DEC_SP, 0x3B, 8, 0, 0, 0)


// SWAP Instructions

decl_instruction(SWAP_AX, 0xCB37, 8, 0, 0, 0)
decl_instruction(SWAP_BX, 0xCB30, 8, 0, 0, 0)
decl_instruction(SWAP_CX, 0xCB31, 8, 0, 0, 0)
decl_instruction(SWAP_DX, 0xCB32, 8, 0, 0, 0)
decl_instruction(SWAP_EX, 0xCB33, 8, 0, 1, 0)
decl_instruction(SWAP_HX, 0xCB34, 8, 0, 0, 0)
decl_instruction(SWAP_LX, 0xCB35, 8, 0, 0, 0)
decl_instruction(SWAP_HL, 0xCB36, 16, 1, 1, 0) 

decl_instruction(DAA, 0x27, 4, 0, 0, 0)
decl_instruction(CPL, 0x2F, 4, 0, 0, 0)
decl_instruction(CCF, 0x3F, 4, 0, 0, 0)
decl_instruction(SCF, 0x37, 4, 0, 0, 0)


// BIT Instructions

decl_instruction(BIT_0A, 0xCB47, 8, 0, 0, 0)
decl_instruction(BIT_1A, 0xCB4F, 8, 0, 0, 0)
decl_instruction(BIT_2A, 0xCB57, 8, 0, 0, 0)
decl_instruction(BIT_3A, 0xCB5F, 8, 0, 0, 0)
decl_instruction(BIT_4A, 0xCB67, 8, 0, 0, 0)
decl_instruction(BIT_5A, 0xCB6F, 8, 0, 0, 0)
decl_instruction(BIT_6A, 0xCB77, 8, 0, 0, 0)
decl_instruction(BIT_7A, 0xCB7F, 8, 0, 0, 0)   

decl_instruction(BIT_0B, 0xCB40, 8, 0, 0, 0)
decl_instruction(BIT_1B, 0xCB48, 8, 0, 0, 0)
decl_instruction(BIT_2B, 0xCB50, 8, 0, 0, 0)
decl_instruction(BIT_3B, 0xCB58, 8, 0, 0, 0)
decl_instruction(BIT_4B, 0xCB60, 8, 0, 0, 0)
decl_instruction(BIT_5B, 0xCB68, 8, 0, 0, 0)
decl_instruction(BIT_6B, 0xCB70, 8, 0, 0, 0)
decl_instruction(BIT_7B, 0xCB78, 8, 0, 0, 0) 

decl_instruction(BIT_0C, 0xCB41, 8, 0, 0, 0)
decl_instruction(BIT_1C, 0xCB49, 8, 0, 0, 0)
decl_instruction(BIT_2C, 0xCB51, 8, 0, 0, 0)
decl_instruction(BIT_3C, 0xCB59, 8, 0, 0, 0)
decl_instruction(BIT_4C, 0xCB61, 8, 0, 0, 0)
decl_instruction(BIT_5C, 0xCB69, 8, 0, 0, 0)
decl_instruction(BIT_6C, 0xCB71, 8, 0, 0, 0)
decl_instruction(BIT_7C, 0xCB79, 8, 0, 0, 0)

decl_instruction(BIT_0D, 0xCB42, 8, 0, 0, 0)
decl_instruction(BIT_1D, 0xCB4A, 8, 0, 0, 0)
decl_instruction(BIT_2D, 0xCB52, 8, 0, 0, 0)
decl_instruction(BIT_3D, 0xCB5A, 8, 0, 0, 0)
decl_instruction(BIT_4D, 0xCB62, 8, 0, 0, 0)
decl_instruction(BIT_5D, 0xCB6A, 8, 0, 0, 0)
decl_instruction(BIT_6D, 0xCB72, 8, 0, 0, 0)
decl_instruction(BIT_7D, 0xCB7A, 8, 0, 0, 0)

decl_instruction(BIT_0E, 0xCB43, 8, 0, 0, 0)
decl_instruction(BIT_1E, 0xCB4B, 8, 0, 0, 0)
decl_instruction(BIT_2E, 0xCB53, 8, 0, 0, 0)
decl_instruction(BIT_3E, 0xCB5B, 8, 0, 0, 0)
decl_instruction(BIT_4E, 0xCB63, 8, 0, 0, 0)
decl_instruction(BIT_5E, 0xCB6B, 8, 0, 0, 0)
decl_instruction(BIT_6E, 0xCB73, 8, 0, 0, 0)
decl_instruction(BIT_7E, 0xCB7B, 8, 0, 0, 0)

decl_instruction(BIT_0H, 0xCB44, 8, 0, 0, 0)
decl_instruction(BIT_1H, 0xCB4C, 8, 0, 0, 0)
decl_instruction(BIT_2H, 0xCB54, 8, 0, 0, 0)
decl_instruction(BIT_3H, 0xCB5C, 8, 0, 0, 0)
decl_instruction(BIT_4H, 0xCB64, 8, 0, 0, 0)
decl_instruction(BIT_5H, 0xCB6C, 8, 0, 0, 0)
decl_instruction(BIT_6H, 0xCB74, 8, 0, 0, 0)
decl_instruction(BIT_7H, 0xCB7C, 8, 0, 0, 0) 

decl_instruction(BIT_0L, 0xCB45, 8, 0, 0, 0)
decl_instruction(BIT_1L, 0xCB4D, 8, 0, 0, 0)
decl_instruction(BIT_2L, 0xCB55, 8, 0, 0, 0)
decl_instruction(BIT_3L, 0xCB5D, 8, 0, 0, 0)
decl_instruction(BIT_4L, 0xCB65, 8, 0, 0, 0)
decl_instruction(BIT_5L, 0xCB6D, 8, 0, 0, 0)
decl_instruction(BIT_6L, 0xCB75, 8, 0, 0, 0)
decl_instruction(BIT_7L, 0xCB7D, 8, 0, 0, 0)

decl_instruction(BIT_0HL, 0xCB46, 16, 0, 0, 0)
decl_instruction(BIT_1HL, 0xCB4E, 16, 0, 0, 0)
decl_instruction(BIT_2HL, 0xCB56, 16, 0, 0, 0)
decl_instruction(BIT_3HL, 0xCB5E, 16, 0, 0, 0)
decl_instruction(BIT_4HL, 0xCB66, 16, 0, 0, 0)
decl_instruction(BIT_5HL, 0xCB6E, 16, 0, 0, 0)
decl_instruction(BIT_6HL, 0xCB76, 16, 0, 0, 0)
decl_instruction(BIT_7HL, 0xCB7E, 16, 0, 0, 0) 

//SET Instructions

decl_instruction(SET_0A, 0xCBC7, 8, 0, 0, 0)
decl_instruction(SET_1A, 0xCBCF, 8, 0, 0, 0)
decl_instruction(SET_2A, 0xCBD7, 8, 0, 0, 0)
decl_instruction(SET_3A, 0xCBDF, 8, 0, 0, 0)
decl_instruction(SET_4A, 0xCBE7, 8, 0, 0, 0)
decl_instruction(SET_5A, 0xCBEF, 8, 0, 0, 0)
decl_instruction(SET_6A, 0xCBF7, 8, 0, 0, 0)
decl_instruction(SET_7A, 0xCBFF, 8, 0, 0, 0)

decl_instruction(SET_0B, 0xCBC0, 8, 0, 0, 0)
decl_instruction(SET_1B, 0xCBC8, 8, 0, 0, 0)
decl_instruction(SET_2B, 0xCBD0, 8, 0, 0, 0)
decl_instruction(SET_3B, 0xCBD8, 8, 0, 0, 0)
decl_instruction(SET_4B, 0xCBE0, 8, 0, 0, 0)
decl_instruction(SET_5B, 0xCBE8, 8, 0, 0, 0)
decl_instruction(SET_6B, 0xCBF0, 8, 0, 0, 0)
decl_instruction(SET_7B, 0xCBF8, 8, 0, 0, 0)

decl_instruction(SET_0C, 0xCBC1, 8, 0, 0, 0)
decl_instruction(SET_1C, 0xCBC9, 8, 0, 0, 0)
decl_instruction(SET_2C, 0xCBD1, 8, 0, 0, 0)
decl_instruction(SET_3C, 0xCBD9, 8, 0, 0, 0)
decl_instruction(SET_4C, 0xCBE1, 8, 0, 0, 0)
decl_instruction(SET_5C, 0xCBE9, 8, 0, 0, 0)
decl_instruction(SET_6C, 0xCBF1, 8, 0, 0, 0)
decl_instruction(SET_7C, 0xCBF9, 8, 0, 0, 0)

decl_instruction(SET_0D, 0xCBC2, 8, 0, 0, 0)
decl_instruction(SET_1D, 0xCBCA, 8, 0, 0, 0)
decl_instruction(SET_2D, 0xCBD2, 8, 0, 0, 0)
decl_instruction(SET_3D, 0xCBDA, 8, 0, 0, 0)
decl_instruction(SET_4D, 0xCBE2, 8, 0, 0, 0)
decl_instruction(SET_5D, 0xCBEA, 8, 0, 0, 0)
decl_instruction(SET_6D, 0xCBF2, 8, 0, 0, 0)
decl_instruction(SET_7D, 0xCBFA, 8, 0, 0, 0)

decl_instruction(SET_0E, 0xCBC3, 8, 0, 0, 0)
decl_instruction(SET_1E, 0xCBCB, 8, 0, 0, 0)
decl_instruction(SET_2E, 0xCBD3, 8, 0, 0, 0)
decl_instruction(SET_3E, 0xCBD5, 8, 0, 0, 0)
decl_instruction(SET_4E, 0xCBE3, 8, 0, 0, 0)
decl_instruction(SET_5E, 0xCBEB, 8, 0, 0, 0)
decl_instruction(SET_6E, 0xCBF3, 8, 0, 0, 0)
decl_instruction(SET_7E, 0xCBFB, 8, 0, 0, 0)

decl_instruction(SET_0H, 0xCBC4, 8, 0, 0, 0)
decl_instruction(SET_1H, 0xCBCC, 8, 0, 0, 0)
decl_instruction(SET_2H, 0xCBD4, 8, 0, 0, 0)
decl_instruction(SET_3H, 0xCBDC, 8, 0, 0, 0)
decl_instruction(SET_4H, 0xCBE4, 8, 0, 0, 0)
decl_instruction(SET_5H, 0xCBEC, 8, 0, 0, 0)
decl_instruction(SET_6H, 0xCBF4, 8, 0, 0, 0)
decl_instruction(SET_7H, 0xCBFC, 8, 0, 0, 0)

decl_instruction(SET_0L, 0xCBC5, 8, 0, 0, 0)
decl_instruction(SET_1L, 0xCBCD, 8, 0, 0, 0)
decl_instruction(SET_2L, 0xCBD5, 8, 0, 0, 0)
decl_instruction(SET_3L, 0xCBDD, 8, 0, 0, 0)
decl_instruction(SET_4L, 0xCBE5, 8, 0, 0, 0)
decl_instruction(SET_5L, 0xCBED, 8, 0, 0, 0)
decl_instruction(SET_6L, 0xCBF5, 8, 0, 0, 0)
decl_instruction(SET_7L, 0xCBFD, 8, 0, 0, 0)

decl_instruction(SET_0HL, 0xCBC6, 16, 0, 0, 0)
decl_instruction(SET_1HL, 0xCBCE, 16, 0, 0, 0)
decl_instruction(SET_2HL, 0xCBD6, 16, 0, 0, 0)
decl_instruction(SET_3HL, 0xCBDE, 16, 0, 0, 0)
decl_instruction(SET_4HL, 0xCBE6, 16, 0, 0, 0)
decl_instruction(SET_5HL, 0xCBEE, 16, 0, 0, 0)
decl_instruction(SET_6HL, 0xCBF6, 16, 0, 0, 0)
decl_instruction(SET_7HL, 0xCBFE, 16, 0, 0, 0) 


// RES Instructions

decl_instruction(RES_0A, 0xCB87, 8, 0, 0, 0)
decl_instruction(RES_1A, 0xCB8F, 8, 0, 0, 0)
decl_instruction(RES_2A, 0xCB97, 8, 0, 0, 0)
decl_instruction(RES_3A, 0xCB9F, 8, 0, 0, 0)
decl_instruction(RES_4A, 0xCBA7, 8, 0, 0, 0)
decl_instruction(RES_5A, 0xCBAF, 8, 0, 0, 0)
decl_instruction(RES_6A, 0xCBB7, 8, 0, 0, 0)
decl_instruction(RES_7A, 0xCBBF, 8, 0, 0, 0)

decl_instruction(RES_0B, 0xCB80, 8, 0, 0, 0)
decl_instruction(RES_1B, 0xCB88, 8, 0, 0, 0)
decl_instruction(RES_2B, 0xCB90, 8, 0, 0, 0)
decl_instruction(RES_3B, 0xCB98, 8, 0, 0, 0)
decl_instruction(RES_4B, 0xCBA0, 8, 0, 0, 0)
decl_instruction(RES_5B, 0xCBA8, 8, 0, 0, 0)
decl_instruction(RES_6B, 0xCBB0, 8, 0, 0, 0)
decl_instruction(RES_7B, 0xCBB8, 8, 0, 0, 0)

decl_instruction(RES_0C, 0xCB81, 8, 0, 0, 0)
decl_instruction(RES_1C, 0xCB89, 8, 0, 0, 0)
decl_instruction(RES_2C, 0xCB91, 8, 0, 0, 0)
decl_instruction(RES_3C, 0xCB99, 8, 0, 0, 0)
decl_instruction(RES_4C, 0xCBA1, 8, 0, 0, 0)
decl_instruction(RES_5C, 0xCBA9, 8, 0, 0, 0)
decl_instruction(RES_6C, 0xCBB1, 8, 0, 0, 0)
decl_instruction(RES_7C, 0xCBB9, 8, 0, 0, 0)  

decl_instruction(RES_0D, 0xCB82, 8, 0, 0, 0)
decl_instruction(RES_1D, 0xCB8A, 8, 0, 0, 0)
decl_instruction(RES_2D, 0xCB92, 8, 0, 0, 0)
decl_instruction(RES_3D, 0xCB9A, 8, 0, 0, 0)
decl_instruction(RES_4D, 0xCBA2, 8, 0, 0, 0)
decl_instruction(RES_5D, 0xCBAA, 8, 0, 0, 0)
decl_instruction(RES_6D, 0xCBB2, 8, 0, 0, 0)
decl_instruction(RES_7D, 0xCBBA, 8, 0, 0, 0)

decl_instruction(RES_0E, 0xCB83, 8, 0, 0, 0)
decl_instruction(RES_1E, 0xCB8B, 8, 0, 0, 0)
decl_instruction(RES_2E, 0xCB93, 8, 0, 0, 0)
decl_instruction(RES_3E, 0xCB95, 8, 0, 0, 0)
decl_instruction(RES_4E, 0xCBA3, 8, 0, 0, 0)
decl_instruction(RES_5E, 0xCBAB, 8, 0, 0, 0)
decl_instruction(RES_6E, 0xCBB3, 8, 0, 0, 0)
decl_instruction(RES_7E, 0xCBBB, 8, 0, 0, 0)

decl_instruction(RES_0H, 0xCB84, 8, 0, 0, 0)
decl_instruction(RES_1H, 0xCB8C, 8, 0, 0, 0)
decl_instruction(RES_2H, 0xCB94, 8, 0, 0, 0)
decl_instruction(RES_3H, 0xCB9C, 8, 0, 0, 0)
decl_instruction(RES_4H, 0xCBA4, 8, 0, 0, 0)
decl_instruction(RES_5H, 0xCBAC, 8, 0, 0, 0)
decl_instruction(RES_6H, 0xCBB4, 8, 0, 0, 0)
decl_instruction(RES_7H, 0xCBBC, 8, 0, 0, 0)

decl_instruction(RES_0L, 0xCB85, 8, 0, 0, 0)
decl_instruction(RES_1L, 0xCB8D, 8, 0, 0, 0)
decl_instruction(RES_2L, 0xCB95, 8, 0, 0, 0)
decl_instruction(RES_3L, 0xCB9D, 8, 0, 0, 0)
decl_instruction(RES_4L, 0xCBA5, 8, 0, 0, 0)
decl_instruction(RES_5L, 0xCBAD, 8, 0, 0, 0)
decl_instruction(RES_6L, 0xCBB5, 8, 0, 0, 0)
decl_instruction(RES_7L, 0xCBBD, 8, 0, 0, 0)  

decl_instruction(RES_0HL, 0xCB86, 16, 0, 0, 0)
decl_instruction(RES_1HL, 0xCB8E, 16, 0, 0, 0)
decl_instruction(RES_2HL, 0xCB96, 16, 0, 0, 0)
decl_instruction(RES_3HL, 0xCB9E, 16, 0, 0, 0)
decl_instruction(RES_4HL, 0xCBA6, 16, 0, 0, 0)
decl_instruction(RES_5HL, 0xCBAE, 16, 0, 0, 0)
decl_instruction(RES_6HL, 0xCBB6, 16, 0, 0, 0)
decl_instruction(RES_7HL, 0xCBBE, 16, 0, 0, 0)   

// RRC Instructions

decl_instruction(RRCA, 0x0F, 8, 0, 0, 0)

decl_instruction(RRC_AX, 0xCB0F, 8, 0, 0, 0)
decl_instruction(RRC_BX, 0xCB08, 8, 0, 0, 0)
decl_instruction(RRC_CX, 0xCB09, 8, 0, 0, 0)
decl_instruction(RRC_DX, 0xCB0A, 8, 0, 0, 0)
decl_instruction(RRC_EX, 0xCB0B, 8, 0, 0, 0)
decl_instruction(RRC_HX, 0xCB0C, 8, 0, 0, 0)
decl_instruction(RRC_LX, 0xCB0D, 8, 0, 0, 0)
decl_instruction(RRC_HL, 0xCB0E, 16, 0, 0, 0) 

// RLC Instructions

decl_instruction(RLCA, 0x07, 8, 0, 0, 0)

decl_instruction(RLC_AX, 0xCB07, 8, 0, 0, 0)
decl_instruction(RLC_BX, 0xCB00, 8, 0, 0, 0)
decl_instruction(RLC_CX, 0xCB01, 8, 0, 0, 0)
decl_instruction(RLC_DX, 0xCB02, 8, 0, 0, 0)
decl_instruction(RLC_EX, 0xCB03, 8, 0, 0, 0)
decl_instruction(RLC_HX, 0xCB04, 8, 0, 0, 0)
decl_instruction(RLC_LX, 0xCB05, 8, 0, 0, 0)
decl_instruction(RLC_HL, 0xCB06, 16, 0, 0, 0)   

// RL Instructions

decl_instruction(RLA, 0x17, 8, 0, 0, 0)

decl_instruction(RL_AX, 0xCB17, 8, 0, 0, 0)
decl_instruction(RL_BX, 0xCB10, 8, 0, 0, 0)
decl_instruction(RL_CX, 0xCB11, 8, 0, 0, 0)
decl_instruction(RL_DX, 0xCB12, 8, 0, 0, 0)
decl_instruction(RL_EX, 0xCB13, 8, 0, 0, 0)
decl_instruction(RL_HX, 0xCB14, 8, 0, 0, 0)
decl_instruction(RL_LX, 0xCB15, 8, 0, 0, 0)
decl_instruction(RL_HL, 0xCB16, 16, 0, 0, 0)

// RR Instructions

decl_instruction(RRA, 0x1F, 8, 0, 0, 0)

decl_instruction(RR_AX, 0xCB1F, 8, 0, 0, 0)
decl_instruction(RR_BX, 0xCB18, 8, 0, 0, 0)
decl_instruction(RR_CX, 0xCB19, 8, 0, 0, 0)
decl_instruction(RR_DX, 0xCB1A, 8, 0, 0, 0)
decl_instruction(RR_EX, 0xCB1B, 8, 0, 0, 0)
decl_instruction(RR_HX, 0xCB1C, 8, 0, 0, 0)
decl_instruction(RR_LX, 0xCB1D, 8, 0, 0, 0)
decl_instruction(RR_HL, 0xCB1E, 16, 0, 0, 0) 


// SLA Instructions

decl_instruction(SLA_AX, 0xCB27, 8, 0, 0, 0)
decl_instruction(SLA_BX, 0xCB20, 8, 0, 0, 0)
decl_instruction(SLA_CX, 0xCB21, 8, 0, 0, 0)
decl_instruction(SLA_DX, 0xCB22, 8, 0, 0, 0)
decl_instruction(SLA_EX, 0xCB23, 8, 0, 0, 0)
decl_instruction(SLA_HX, 0xCB24, 8, 0, 0, 0)
decl_instruction(SLA_LX, 0xCB25, 8, 0, 0, 0)
decl_instruction(SLA_HL, 0xCB26, 16, 0, 0, 0)

// SRA Instructions

decl_instruction(SRA_AX, 0xCB2F, 8, 0, 0, 0)
decl_instruction(SRA_BX, 0xCB28, 8, 0, 0, 0)
decl_instruction(SRA_CX, 0xCB29, 8, 0, 0, 0)
decl_instruction(SRA_DX, 0xCB2A, 8, 0, 0, 0)
decl_instruction(SRA_EX, 0xCB2B, 8, 0, 0, 0)
decl_instruction(SRA_HX, 0xCB2C, 8, 0, 0, 0)
decl_instruction(SRA_LX, 0xCB2D, 8, 0, 0, 0)
decl_instruction(SRA_HL, 0xCB2E, 16, 0, 0, 0)

// SRL Instructions

decl_instruction(SRL_AX, 0xCB3F, 8, 0, 0, 0)
decl_instruction(SRL_BX, 0xCB38, 8, 0, 0, 0)
decl_instruction(SRL_CX, 0xCB39, 8, 0, 0, 0)
decl_instruction(SRL_DX, 0xCB3A, 8, 0, 0, 0)
decl_instruction(SRL_EX, 0xCB3B, 8, 0, 0, 0)
decl_instruction(SRL_HX, 0xCB3C, 8, 0, 0, 0)
decl_instruction(SRL_LX, 0xCB3D, 8, 0, 0, 0)
decl_instruction(SRL_HL, 0xCB3E, 16, 0, 0, 0)

//HALT

decl_instruction(HALT, 0x76, 4, 0, 0, 0)

// STOP

decl_instruction(STOP, 0x10, 4, 0, 0, 0)

// EI/DI

decl_instruction(EI, 0xFB, 4, 0, 0, 0)
decl_instruction(DI, 0xF3, 4, 0, 0, 0)

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


decl_instruction(RST_0x00, 0xC7, 32, 0, 0, 0)
decl_instruction(RST_0x08, 0xCF, 32, 0, 0, 0)
decl_instruction(RST_0x10, 0xD7, 32, 0, 0, 0)
decl_instruction(RST_0x18, 0xDF, 32, 0, 0, 0)
decl_instruction(RST_0x20, 0xE7, 32, 0, 0, 0)
decl_instruction(RST_0x28, 0xEF, 32, 0, 0, 0)
decl_instruction(RST_0x30, 0xF7, 32, 0, 0, 0)
decl_instruction(RST_0x38, 0xFF, 32, 0, 0, 0)

decl_instruction(RET, 0xC9, 8, 0, 0, 0)
decl_instruction(RETNZ, 0xC0, 8, 0, 0, 0)
decl_instruction(RETZ, 0xC8, 8, 0, 0, 0)
decl_instruction(RETNC, 0xD0, 8, 0, 0, 0)
decl_instruction(RETC, 0xD8, 8, 0, 0, 0)
decl_instruction(RETI, 0xD9, 8, 0, 0, 0)
