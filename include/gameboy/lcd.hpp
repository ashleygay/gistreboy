/*
 * File : lcd.hpp
 *
 * File created by : Corentin Gay
 * File was created at : 01/12/2017
 */

#pragma once

#include <interrupthandler.hpp>

class LCD
{
	public:
		LCD(InterruptHandler &it, Memory &mem) :
		_it(it),
		_mem(mem){}

		int step();

	private:
		InterruptHandler &_it;
		Memory &_mem;
};
