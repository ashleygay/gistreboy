#pragma once

#include <iostream>

#include <debug.hpp>
#include <instructionargs.hpp>

// Args are of the forme "const InstructionArgs& args"
#define decl_instr_execute(name, content)\
	void name::execute() { content };

class Instruction {
	public:
		virtual void exec(InstructionArgs& args) = 0;
		virtual const char *toStr() = 0;
		virtual int opCode() = 0;
		virtual int nbCycles() = 0;
};

class Nop : Instruction {
	public:
		void exec(InstructionArgs& args) {(void)args;}
		const char *toStr() { return "NOP"; }
		virtual int opcode() { return 0; }
		virtual int nbCycles() { return 4; }
};

/// LD Instructions

#define decl_instruction(name, opc, nbr)\
	class name : Instruction{\
		public:\
			virtual void exec(InstructionArgs& args);\
			virtual const char *toStr() { return #name; }\
			virtual int opCode() { return opc; } \
			virtual int nbCycles() { return nbr; } \
	}; \

