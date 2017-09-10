#pragma once

// Args are of the forme "const InstructionArgs& args"
#define decl_instr_execute(name, content)\
	void name::execute() { content };

class Instruction {
	public:
		virtual void exec(Processor& p, const InstructionArgs& args) = 0;
		virtual const char *toStr() = 0;
		virtual int opCode() = 0;
		virtual int nbCycles() = 0;
};

class Nop : Instruction {
	public:
		void exec(Processor& p, const InstructionArgs& args) {(void)args;}
		const char *toStr() { return "NOP"; }
		virtual int opcode() { return 0; }
		virtual int nbCycles() { return 4; }
};



/// LD Instructions

#define decl_instruction(name, opc, nbr, content)\
	class name : Instruction{\
		public:\
			virtual void exec(Processor& p, const InstructionArgs& args)\
			virtual const char *toStr() { return #name; }\
			virtual int opCode() { return opc; } \
			virtual int nbCycles() { return nbr; } \
	}; \
	void name::execute(Processor &p, const InstructionArgs& args) { content }

#define LD_BX_EXEC \
	DEBUG_PRINT << "args.first_arg is " << args.first_arg \
	<< "\nargs.second_arg is " << args.second_arg << std::endl; 

decl_instruction(LD_BX, 0x06, 8, LD_BX_EXEC)

decl_instruction(LD_CX, 0x0E, 8,)

decl_instruction(LD_DX, 0x16, 8,)

decl_instruction(LD_EX, 0x1E, 8,)

decl_instruction(LD_HX, 0x26, 8,)

decl_instruction(LD_LX, 0x2E, 8,)
