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


decl_LD_Instruct_Cst(LD_BX)
decl_instr_opcode(LD_BX, 0x06)
decl_instr_cycles(LD_BX, 8)

decl_LD_Instruct_Cst(LD_CX)
decl_instr_opcode(LD_CX, 0x0E)
decl_instr_cycles(LD_CX, 8)

decl_LD_Instruct_Cst(LD_DX)
decl_instr_opcode(LD_DX, 0x16)
decl_instr_cycles(LD_DX, 8)

decl_LD_Instruct_Cst(LD_EX)
decl_instr_opcode(LD_EX, 0x1E)
decl_instr_cycles(LD_EX, 8)

decl_LD_Instruct_Cst(LD_HX)
decl_instr_opcode(LD_HX, 0x26)
decl_instr_cycles(LD_HX, 8)

decl_LD_Instruct_Cst(LD_LX)
decl_instr_opcode(LD_LX, 0x2E)
decl_instr_cycles(LD_LX, 8)
