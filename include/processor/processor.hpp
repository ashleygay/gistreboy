/*
 * File : processor.hpp
 *
 * This file represents the processor class
 *
 * File created by : Arnaud Bastie
 * File was created the : 29/08/2017
 */

#pragma once

#include <iostream>

class InstructionSet;
class InterruptHandler;
class Memory;

#include <debug.hpp>
#include <instructionset.hpp>
#include <instructionargs.hpp>
#include <registers.hpp>
#include <opcode.hpp>
#include <atomic>
#include <exception>

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
			PC.value = 0x0000;
			SP.value = 0xfffe;
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

		DRegister PC;
		DRegister SP;

	private:
		// Boolean is set to false when we end the bootcode.
		bool isBooting = true;

		Instruction * currentInstruction;

		// InstructionSet containing all instructions.
		InstructionSet iset;

		// Interrupt Handler, will handle all interrupts
		InterruptHandler *_handler = nullptr;

		// Used to resolve all memory operations
		// Read/Write as wall as charging next instruction etc
		Memory *_mem = nullptr;

		// They cannot be both true at the same time
		bool halted = false;
		bool stopped = false;

	public:
		//Function used by the gameboy class
		// returns the number of cycles that takes the instruction
		int step();

		// Those functions are used by the instructions to read/write
		// memory values
		uint8_t _read(uint16_t address);

		void _write(uint8_t value, uint16_t address);

		void setInterruptHandler(InterruptHandler *handler)
			{_handler = handler;}

		void setMemory(Memory *mem)
			{_mem = mem;}

		// Enable/Disable IME
		void enableIME();
		void disableIME();

		// Delayed version should be called from EI instruction only
		void enableIMEDelay();

		// Enter halt mode,
		// If (IF & IE) => an interrupt is enabled and active
		// then we leave halt mode
		// the behavior is then dependant on IME
		//
		// if IME is active we execute the interrupt and clean IF.
		//
		// if IME is not active then we continue execution of
		// instructions and we do not clean IF.
		void HALT();


		// Enter stop mode
		// Disable all interrupts except JOYPAD
		// The programmer should clear IE before stopping
		// The programmer must select bits prior to entering
		// stop mode in order to be able to leave it correctly
		void STOP();
	private:
		int _execCurrentInstruction();

		void _BUG(std::string str, int value) const;

		void _fetchNextInstruction();
	public:
		Processor(Processor const&) = delete;
		void operator=(Processor const&)  = delete;
};
