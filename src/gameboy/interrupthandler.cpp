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
			//TODO: get interrupt from memory, & them and get
			// associated power of 2 to get the correct routine
			return 42;
		}
	}
}

void InterruptHandler::_interruptLCD() 
{
	//TODO
}

void InterruptHandler::_interruptVBLANK() 
{
	//TODO
}

void InterruptHandler::_interruptSerial()
{
	//TODO
}

void InterruptHandler::_interruptJoypad()
{
	//TODO
}
