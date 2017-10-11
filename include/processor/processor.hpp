#pragma once

#include <iostream>

class InstructionSet;

#include <debug.hpp>
#include <instructionset.hpp>
#include <instructionargs.hpp>
#include <registers.hpp>
#include <opcode.hpp>
#include <atomic>

class Processor {

	public:
		Processor()
		{
			// Default values taken from TCAGBD docs
			A.value = 0x01;
			B.value = 0x00;
			C.value = 0x13;
			D.value = 0x00;
			E.value = 0xD8;
			H.value = 0x01;
			L.value = 0x4D;
			PC.value = 0x100;
			SP.value = 0xfffe;

			// Interrupts are enabled at the start
			IME.value = 1;

			// We enable all kinds of interrupts
			IE.setInterrupt(InterruptRegister::VBLANK);
			IE.setInterrupt(InterruptRegister::LCD_STATUS);
			IE.setInterrupt(InterruptRegister::TIMER);
			IE.setInterrupt(InterruptRegister::SERIAL);
			IE.setInterrupt(InterruptRegister::JOYPAD);
		}

	public:
		FlagRegister flag;

		Register A;
		Register B;
		Register C;
		Register D;
		Register E;
		Register H;
		Register L;

		// Enable/disable all interrupts
		Register IME;

		// Enable/disable specific interrupts
		InterruptRegister IE;

		// This flag is set when an interrupt is pending
		InterruptRegister IF;

		// Used to resolve all memory operations
		// Read/Write as wall as charging next instruction etc
		// Memory mem;

		DRegister PC;
		DRegister SP;

		// Boolean is set to false when we end the bootcode.
		bool isBooting = true;

		Instruction * currentInstruction;

		// InstructionSet containing all instructions.
		InstructionSet iset;
	public:
		// Those functions are used by the instructions to read/write
		// memory values
/*
		uint8_t _read(uint16_t address) {return mem.read(address);}
		void _write(uint8_t value, uint16_t address)
			{mem.write(value, address);}
*/
	private:
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
