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
			std::bitset<8> IF = 0; /*_m->getInterruptFlags();*/
			std::bitset<8> IE = 0; /*_m->getInterruptEnable();*/
			std::bitset<8> res = IF & IE;

			// We compute the nth interrupt index
			int index = 0;
			for (; !res[index] && index < 8; ++index);

			// We set the cleanup routine and the execution of
			// the interrupt.
			if (res.any()) {
				unsigned long i = res.to_ulong();
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
	return 4560;
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
