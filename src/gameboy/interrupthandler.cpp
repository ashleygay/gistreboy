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

			return res ? _interruptRoutines[res](): 0;
		}
	}
}

int InterruptHandler::_NONE()
{
	//In theory, this should never be called

	uint8_t IF = 0; /*_m->getInterruptFlags();*/
	uint8_t IE = 0; /*_m->getInterruptEnable();*/

	DEBUG_STREAM << "Interrupt 0 called, something went wrong" << std::endl;
	DEBUG_STREAM << "Interrupt Flags :" << std::bitset<8>(IF) << std::endl;
	DEBUG_STREAM << "Interrupt Enable :" << std::bitset<8>(IE) << std::endl;

	return 0;
}

int InterruptHandler::_LCD_STATUS()
{
	//Changes permissions to be able to write to VRAM/OAM
	// _mem->VBLANK();
	return 4560;
}

int InterruptHandler::_VBLANK()
{
	//TODO
	return 1;
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
