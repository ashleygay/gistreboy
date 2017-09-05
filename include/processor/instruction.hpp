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



/// LD Instructions

#define decl_LD_Instruct_Cst(name)\
	class name : Instruction, LD_RegCst {\
		public:\
			using LD_RegCst::LD_RegCst;\
			virtual void execute();\
			virtual const char *toStr() { return #name; };\
			static int opcode(); \
			static int nbCycles(); \
	};

struct LD_RegCst {
	LD_RegCst(char val)
	{
		this->value = val;
	}
	char value;
};
