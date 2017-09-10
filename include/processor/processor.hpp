#pragma once

#include <iostream>

#include <debug.hpp>
#include <instructionargs.hpp>
#include <registers.hpp>

class Processor {

	using OpCode = uint16_t;
	public:
		static Processor& getInstance() {
			static Processor inst;
			return inst;
		}
		
		void execCurrentInstruction();

		FlagRegister flagReg;

		Register registerA;
		Register registerB;
		Register registerC;
		Register registerD;
		Register registerE;
		Register registerH;
		Register registerL;

		// OpCode of the curent instruction
		// OpCode opc;
		// Used to resolve all memory operations
		// Read/Write as wall as charging next instruction etc
		//MemoryAccessor mem;

	private:
		DRegister programCounter;
		DRegister stackPointer;

		//TODO: structure for arguments of current instruction
		InstructionArgs args;
		OpCode currentOpCode;


	private:
		Processor()
		{
			programCounter.value = 0x100;
			stackPointer.value = 0xfffe;
		}

	public:
 		// Get the number of cycles of the current instruction to execute
		int getNbCycles() const;
		void fetchNextInstruction();

		Processor(Processor const&) = delete;
		void operator=(Processor const&)  = delete;
};
