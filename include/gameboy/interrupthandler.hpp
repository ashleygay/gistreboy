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

struct Interrupt
{
	// Function that will be executed to handle the interrupt
	std::function<int()> exec;

	// Function called on the next doInterrupt()
	// IE: for VBLANK it reverses the permissions and denies the access
	// to the memory
	std::function<void()> cleanup;
};

class InterruptHandler
{
	public:
		// Execute current interrupt.
		// Returns the number of cycles it should take.
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
		void _NONE();

		//VBLANK:
		// triggered once per frame (60fps)
		// Duration : 4560 clock cycles
		// During those cycles, video memory can be accessed freely
		// It is not triggered by turning on or off the LCD screen
		// It is only triggered when THE VBL starts (Mode 1 for LCD)
		int _VBLANK();
		void _VBLANK_END();

		//TODO
		int _LCD_STATUS();

		//TODO
		int _SERIAL();

		//JOYPAD:
		// Used by the programmer to read values from the JOYPAD
		// Is usually used to get out of the STOP mode.
		//TODO
		int _JOYPAD();


		// TIMER:
		//TODO
		int _TIMER();

		void _resetCleanupRoutine();

	private:
		// Interrupt Master Enable
		bool IME = true;

		// This attribute is used for handling the case when the
		// interrupts are enabled by EI instruction. It allows the
		// gameboy to execute one more instruction before checking the
		// interrupts.
		bool IME_delay = false;

		std::array<Interrupt, 6> _interruptRoutines = {{
			{
				std::bind(&InterruptHandler::_VBLANK, this),
				std::bind(&InterruptHandler::_VBLANK_END, this)
			},
			{
				std::bind(&InterruptHandler::_LCD_STATUS, this),
				std::bind(&InterruptHandler::_NONE, this)
			},
			{
				std::bind(&InterruptHandler::_TIMER, this),
				std::bind(&InterruptHandler::_NONE, this)
			},
			{
				std::bind(&InterruptHandler::_SERIAL, this),
				std::bind(&InterruptHandler::_NONE, this)
			},
			{
				std::bind(&InterruptHandler::_JOYPAD, this),
				std::bind(&InterruptHandler::_NONE, this)
			}
			}};

		std::function<void()> _cleanup =
			std::bind(&InterruptHandler::_NONE, this);

		Processor *_p;
		Memory *_m;
};
