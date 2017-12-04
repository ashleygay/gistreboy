/*
 * File : lcd.cpp
 *
 * File created by : Corentin Gay
 * File was created at : 01/12/2017
 */

#include "lcd.hpp"


LCD::LCD(InterruptHandler &it, Memory &mem) :
		_it(it),
		_video(mem.get_video())
{

}


int LCD::step()
{
	//TODO: do a step of the LCD screen
	return 0;
}

