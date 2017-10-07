#pragma once

#include <iostream>
#include <vector>

#include <debug.hpp>
#include <processor.hpp>
#include <instructionargs.hpp>

class Instruction {
	public:
		virtual void exec() = 0;
		virtual const char *toStr() = 0;
		virtual uint16_t opCode() = 0;
		virtual int nbCycles() = 0;
		virtual int nbArgs() = 0;
		virtual void setArgs(InstructionArgs & args) = 0;
		virtual int argSize(int i) = 0;
};

class Nop : Instruction {
	public:
		void exec() {}
		const char *toStr() { return "NOP"; }
		virtual uint16_t opcode() { return 0; }
		virtual int nbCycles() { return 4; }
		virtual int nbArgs() { return 0; }
		virtual void setArgs(InstructionArgs & args){}
		virtual int argSize(int i) {return 0;}
};

/// LD Instructions

//TODO: if the processor is no longer a singleton, how do we modify it in the
//instructions, modidfying registers for example ?

#define decl_instruction(name, opc, nb_cycles, nb_args, size_arg0, size_arg1)\
	class name : Instruction{\
		public:\
			name();\
			virtual void exec();\
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
