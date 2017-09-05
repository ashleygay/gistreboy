#pragma once

#define decl_instr_opcode(instr, opc)\
	int instr::opcode() { return opc; };

#define decl_instr_cycles(instr, nbr)\
	int instr::nbCycles() { return nbr; };



class Instruction {
	public:
		virtual void execute() = 0;
		virtual const char *toStr() = 0;
};

class Nop : Instruction {
	public:
		void execute() {};
		const char *toStr() { return "NOP"; };
		static int opcode() { return 0; };
		static int nbCycles() { return 4; };
};
