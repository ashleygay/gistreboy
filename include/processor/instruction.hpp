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
