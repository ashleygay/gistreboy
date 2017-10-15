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
// TODO : A, HL
decl_instruction(LD_BA, 0x47, 4, 0, 0, 0)
decl_instruction(LD_BB, 0x40, 4, 0, 0, 0)
decl_instruction(LD_BC, 0x41, 4, 0, 0, 0)
decl_instruction(LD_BD, 0x42, 4, 0, 0, 0)
decl_instruction(LD_BE, 0x43, 4, 0, 0, 0)
decl_instruction(LD_BH, 0x44, 4, 0, 0, 0)
decl_instruction(LD_BL, 0x45, 4, 0, 0, 0)
// TODO : B, HL
decl_instruction(LD_CA, 0x4F, 4, 0, 0, 0)
decl_instruction(LD_CB, 0x48, 4, 0, 0, 0)
decl_instruction(LD_CC, 0x49, 4, 0, 0, 0)
decl_instruction(LD_CD, 0x4A, 4, 0, 0, 0)
decl_instruction(LD_CE, 0x4B, 4, 0, 0, 0)
decl_instruction(LD_CH, 0x4C, 4, 0, 0, 0)
decl_instruction(LD_CL, 0x4D, 4, 0, 0, 0)
// TODO : C, HL
decl_instruction(LD_DA, 0x57, 4, 0, 0, 0)
decl_instruction(LD_DB, 0x50, 4, 0, 0, 0)
decl_instruction(LD_DC, 0x51, 4, 0, 0, 0)
decl_instruction(LD_DD, 0x52, 4, 0, 0, 0)
decl_instruction(LD_DE, 0x53, 4, 0, 0, 0)
decl_instruction(LD_DH, 0x54, 4, 0, 0, 0)
decl_instruction(LD_DL, 0x55, 4, 0, 0, 0)
// TODO : D, HL
decl_instruction(LD_EA, 0x5F, 4, 0, 0, 0)
decl_instruction(LD_EB, 0x58, 4, 0, 0, 0)
decl_instruction(LD_EC, 0x59, 4, 0, 0, 0)
decl_instruction(LD_ED, 0x5A, 4, 0, 0, 0)
decl_instruction(LD_EE, 0x5B, 4, 0, 0, 0)
decl_instruction(LD_EH, 0x5C, 4, 0, 0, 0)
decl_instruction(LD_EL, 0x5D, 4, 0, 0, 0)
// TODO : E, HL
decl_instruction(LD_HA, 0x67, 4, 0, 0, 0)
decl_instruction(LD_HB, 0x60, 4, 0, 0, 0)
decl_instruction(LD_HC, 0x61, 4, 0, 0, 0)
decl_instruction(LD_HD, 0x62, 4, 0, 0, 0)
decl_instruction(LD_HE, 0x63, 4, 0, 0, 0)
decl_instruction(LD_HH, 0x64, 4, 0, 0, 0)
decl_instruction(LD_HL, 0x65, 4, 0, 0, 0)
// TODO : H, HL
decl_instruction(LD_LA, 0x6F, 4, 0, 0, 0)
decl_instruction(LD_LB, 0x68, 4, 0, 0, 0)
decl_instruction(LD_LC, 0x69, 4, 0, 0, 0)
decl_instruction(LD_LD, 0x6A, 4, 0, 0, 0)
decl_instruction(LD_LE, 0x6B, 4, 0, 0, 0)
decl_instruction(LD_LH, 0x6C, 4, 0, 0, 0)
decl_instruction(LD_LL, 0x6D, 4, 0, 0, 0)
// TODO : L, HL
// TODO : HL, B
// TODO : HL, C
// TODO : HL, D
// TODO : HL, E
// TODO : HL, H
// TODO : HL, L
// TODO : HL, n


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
decl_instruction(ADD_AADDRESS, 0xC6, 8, 1, 1, 0)

// ADC Instructions

decl_instruction(ADC_AA, 0x8F, 4, 0, 0, 0)
decl_instruction(ADC_AB, 0x88, 4, 0, 0, 0)
decl_instruction(ADC_AC, 0x89, 4, 0, 0, 0)
decl_instruction(ADC_AD, 0x8A, 4, 0, 0, 0)
decl_instruction(ADC_AE, 0x8B, 4, 0, 0, 0)
decl_instruction(ADC_AH, 0x8C, 4, 0, 0, 0)
decl_instruction(ADC_AL, 0x8D, 4, 0, 0, 0)
decl_instruction(ADC_AHL, 0x8E, 8, 0, 0, 0)
decl_instruction(ADC_AADDRESS, 0xCE, 8, 1, 1, 0) 


// SUB Instructions

decl_instruction(SUB_AA, 0x97, 4, 0, 0, 0)
decl_instruction(SUB_AB, 0x90, 4, 0, 0, 0)
decl_instruction(SUB_AC, 0x91, 4, 0, 0, 0)
decl_instruction(SUB_AD, 0x92, 4, 0, 0, 0)
decl_instruction(SUB_AE, 0x93, 4, 0, 0, 0)
decl_instruction(SUB_AH, 0x94, 4, 0, 0, 0)
decl_instruction(SUB_AL, 0x95, 4, 0, 0, 0)
decl_instruction(SUB_AHL, 0x96, 8, 0, 0, 0)
decl_instruction(SUB_AADDRESS, 0xD6, 8, 1, 1, 0)  

// SBC Instructions

decl_instruction(SBC_AA, 0x9F, 4, 0, 0, 0)
decl_instruction(SBC_AB, 0x98, 4, 0, 0, 0)
decl_instruction(SBC_AC, 0x99, 4, 0, 0, 0)
decl_instruction(SBC_AD, 0x9A, 4, 0, 0, 0)
decl_instruction(SBC_AE, 0x9B, 4, 0, 0, 0)
decl_instruction(SBC_AH, 0x9C, 4, 0, 0, 0)
decl_instruction(SBC_AL, 0x9D, 4, 0, 0, 0)
decl_instruction(SBC_AHL, 0x9E, 8, 0, 0, 0)
//decl_instruction(SBC_AADDRESS, 0xD, 8, 1, 1, 0) pas d'opcode in manual
