#pragma once

#include <iostream>

#include <debug.hpp>
#include <instructionset.hpp>
#include <instructionargs.hpp>
#include <registers.hpp>
#include <opcode.hpp>
#include <atomic>

class Processor {

	public:
		static Processor& getInstance() {
			static Processor inst;
			return inst;
		}
		
		FlagRegister flag;

		Register registerA;
		Register registerB;
		Register registerC;
		Register registerD;
		Register registerE;
		Register registerH;
		Register registerL;

		// Enable interrupts to be used
		Register interruptMasterEnable;

		// Interrupt enable
		Register interruptEnable;

		Register interruptFlag;

		// Used to resolve all memory operations
		// Read/Write as wall as charging next instruction etc
		// Memory mem;

	private:
		DRegister programCounter;
		DRegister stackPointer;

		std::atomic_bool _isRunning = {false};

		Instruction * _currentInstruction;

		// All interupts

		// All interrupts routines here.
		//std::array<>;

		// InstructionSet containing all instructions.
		InstructionSet iset;

	private:
		Processor()
		{
			programCounter.value = 0x100;
			stackPointer.value = 0xfffe;
			interruptMasterEnable.value = 1;
			interruptEnable.value = 1;
		}
		int _BUG(std::string str, int value);
		int _fetchNextInstruction();

	public:
 		// Get the number of cycles of the current instruction to execute
		int getNbCycles() const;

		// Fetch the next instruction/interrupt to do.
		int fetchNextStep();
		void execCurrentInstruction();

	public:
		Processor(Processor const&) = delete;
		void operator=(Processor const&)  = delete;
};
