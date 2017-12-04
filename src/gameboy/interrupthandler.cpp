/*
 * File : interrupthandler.cpp
 *
 * File created by : Corentin Gay
 * File was created the : 09/10/2017
 */

#include <interrupthandler.hpp>

void InterruptHandler::_resetCleanupRoutine()
{
	_cleanup = std::bind(&InterruptHandler::_NONE, this);
}

int InterruptHandler::doInterrupt()
{
	_cleanup();
	_resetCleanupRoutine();

	if (IME_delay) {
		enableIME();
		IME_delay = false;
		return 0;
	}
	else {
		// Interrupts are turned off.
		if (!IME)
			return 0;
		else {
			std::bitset<8> IF = _m->get_interrupt_flags();
			std::bitset<8> IE = _m->get_interrupt_enable();
			std::bitset<8> res = IF & IE;

			// We compute the nth interrupt index
			int index = 0;
			while (!res[index] && (index < 8)) {
				++index;
			}

			// We set the cleanup routine, we clean IF
			// and we execute the interrupt.
			if (res.any()) {
				unsigned long i = res.to_ulong();
				_m->reset_interrupt_flag((Memory::Interrupt)i);
				_cleanup = _interruptRoutines[i].cleanup;
				return _interruptRoutines[i].exec();
			}
			else
				return 0;
		}
	}
}

void InterruptHandler::_NONE()
{
	return;
}

int InterruptHandler::_TIMER()
{
	return 0;
}

int InterruptHandler::_LCD_STATUS()
{
	return 0;
}

int InterruptHandler::_VBLANK()
{
	//TODO
	//Changes permissions to be able to write to VRAM/OAM
	// _mem->VBLANK();
	return 0;
}

void InterruptHandler::_VBLANK_END()
{
	//TODO
	//Changes permissions to disable write to VRAM/OAM
	// _mem->VBLANK_END();
}

int InterruptHandler::_SERIAL()
{
	//TODO
	return 1;
}

int InterruptHandler::_JOYPAD()
{
	//TODO
	return 1;
}
