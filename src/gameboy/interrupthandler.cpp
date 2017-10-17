/*
 * File : interrupthandler.cpp
 *
 * File created by : Corentin Gay
 * File was created the : 09/10/2017
 */

#include <interrupthandler.hpp>


int InterruptHandler::doInterrupt()
{
	if (IME_delay) {
		enableIME();
		this->IME_delay = false;
		return 0;
	}
	else {
		// Interrupts are turned off.
		if (!IME)
			return 0;
		else {
			uint8_t IF = 0; /*_m->getInterruptFlags();*/
			uint8_t IE = 0; /*_m->getInterruptEnable();*/
			uint8_t res = IF & IE;

			int index = 0;

			for (; !(res & 1); ++index)
				res = res >> 1;

			return _interruptRoutines[res]();
		}
	}
}

int InterruptHandler::_interruptLCD()
{
	//TODO
	return 1;
}

int InterruptHandler::_interruptVBLANK()
{
	//TODO
	return 1;
}

int InterruptHandler::_interruptSerial()
{
	//TODO
	return 1;
}

int InterruptHandler::_interruptJoypad()
{
	//TODO
	return 1;
}
