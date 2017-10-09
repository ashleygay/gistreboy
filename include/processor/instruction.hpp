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

/// LD Instructions

#define decl_instruction(name, opc, nb_cycles, nb_args, size_arg0, size_arg1)\
	class name : Instruction{\
		public:\
			name(Processor& p): _p(p){}\
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
			Processor& _p;\
	};

decl_instruction(LD_BX, 0x06, 8, 1, 1, 0)

decl_instruction(NOP, 0x00, 4, 0, 0, 0)
