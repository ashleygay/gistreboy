/*
 * File : interrupthandler.hpp
 *
 * File created by : Corentin Gay
 * File was created at : 08/10/2017
 *
 * This class handles all interrupts as well as enabling and disabling them.
 * The code is used/called by GameBoy and Processor.
 *
 */

#pragma once

#include <functional>

// FIXME Temporary classes only for compilation purposes

class Processor
{
};

class Memory
{
};


class InterruptHandler
{
	public:
		// Execute current interrupt.
		// Returns the number if cycles it should took.
		// Returns 0 if there was no interrupt.
		int doInterrupt();

		// Functions called from Processor
		void enableIME(){IME = true;}
		void enableIMEDelay(){IME_delay = true;}
		void disableIME(){IME = false;}

		void setProcessor(Processor *p){_p = p;}
		void setMemory(Memory *m){_m = m;}
	private:
		// Interrupt routines
		// TODO: actually implement them
		void _interruptLCD();
		void _interruptVBLANK();
		void _interruptSerial();
		void _interruptJoypad();
	private:
		// Interrupt Master Enable
		bool IME = true;

		// This attribute is used for handling the case when the
		// interrupts are enabled by EI instruction. It allows the
		// gameboy to execute on more instruction before checking the
		// interrupts.
		bool IME_delay = false;

		std::array<std::function<void()>, 6> _interruptRoutines = {
			std::bind(&InterruptHandler::_interruptLCD, this),
			std::bind(&InterruptHandler::_interruptVBLANK, this),
			std::bind(&InterruptHandler::_interruptSerial, this),
			std::bind(&InterruptHandler::_interruptJoypad, this)
			};
		Processor *_p;
		Memory *_m;
};
