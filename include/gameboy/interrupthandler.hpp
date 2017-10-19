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
#include <cmath>
#include <debug.hpp>
#include <bitset>

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
		int _NONE();

		//VBLANK:
		// triggered once per frame (60fps)
		// Duration : 4560 clock cycles
		// During those cycles, video memory can be accessed freely
		// It is not triggered by turning on or off the LCD screen
		// It is only triggered when THE VBL starts (Mode 1 for LCD)
		int _VBLANK();

		int _LCD_STATUS();
		int _SERIAL();

		//JOYPAD: 
		// Used by the programmer to read values from the JOYPAD
		// Is usually used to get out of the STOP mode.
		int _JOYPAD();
	private:
		// Interrupt Master Enable
		bool IME = true;

		// This attribute is used for handling the case when the
		// interrupts are enabled by EI instruction. It allows the
		// gameboy to execute on more instruction before checking the
		// interrupts.
		bool IME_delay = false;

		std::array<std::function<int()>, 6> _interruptRoutines = {
			std::bind(&InterruptHandler::_NONE, this),
			std::bind(&InterruptHandler::_LCD_STATUS, this),
			std::bind(&InterruptHandler::_VBLANK, this),
			std::bind(&InterruptHandler::_SERIAL, this),
			std::bind(&InterruptHandler::_JOYPAD, this)
			};
		Processor *_p;
		Memory *_m;
};
