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
decl_instruction(LD_BB, 0x40, 4, 0, 0, 0)
decl_instruction(LD_BC, 0x41, 4, 0, 0, 0)
decl_instruction(LD_BD, 0x42, 4, 0, 0, 0)
decl_instruction(LD_BE, 0x43, 4, 0, 0, 0)
decl_instruction(LD_BH, 0x44, 4, 0, 0, 0)
decl_instruction(LD_BL, 0x45, 4, 0, 0, 0)
// TODO : B, HL
decl_instruction(LD_CB, 0x48, 4, 0, 0, 0)
decl_instruction(LD_CC, 0x49, 4, 0, 0, 0)
decl_instruction(LD_CD, 0x4A, 4, 0, 0, 0)
decl_instruction(LD_CE, 0x4B, 4, 0, 0, 0)
decl_instruction(LD_CH, 0x4C, 4, 0, 0, 0)
decl_instruction(LD_CL, 0x4D, 4, 0, 0, 0)
// TODO : C, HL
decl_instruction(LD_DB, 0x50, 4, 0, 0, 0)
decl_instruction(LD_DC, 0x51, 4, 0, 0, 0)
decl_instruction(LD_DD, 0x52, 4, 0, 0, 0)
decl_instruction(LD_DE, 0x53, 4, 0, 0, 0)
decl_instruction(LD_DH, 0x54, 4, 0, 0, 0)
decl_instruction(LD_DL, 0x55, 4, 0, 0, 0)
// TODO : D, HL
decl_instruction(LD_EB, 0x58, 4, 0, 0, 0)
decl_instruction(LD_EC, 0x59, 4, 0, 0, 0)
decl_instruction(LD_ED, 0x5A, 4, 0, 0, 0)
decl_instruction(LD_EE, 0x5B, 4, 0, 0, 0)
decl_instruction(LD_EH, 0x5C, 4, 0, 0, 0)
decl_instruction(LD_EL, 0x5D, 4, 0, 0, 0)
// TODO : E, HL
decl_instruction(LD_HB, 0x60, 4, 0, 0, 0)
decl_instruction(LD_HC, 0x61, 4, 0, 0, 0)
decl_instruction(LD_HD, 0x62, 4, 0, 0, 0)
decl_instruction(LD_HE, 0x63, 4, 0, 0, 0)
decl_instruction(LD_HH, 0x64, 4, 0, 0, 0)
decl_instruction(LD_HL, 0x65, 4, 0, 0, 0)
// TODO : H, HL
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


decl_instruction(NOP, 0x00, 4, 0, 0, 0)


decl_instruction(ADD_AA, 0x87, 4, 2, 1, 1)
