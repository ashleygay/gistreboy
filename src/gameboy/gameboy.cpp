/*
 * File : gameboy.cpp
 *
 * File created by : Corentin Gay
 * File was created at : 08/10/2017
 */

#include <gameboy.hpp>



void GameBoy::step()
{
	// Priority order:
	// 	Interrupts
	// 	Next Instruction

	// Start chrono here for a cycle
	boost::asio::deadline_timer t(io,
			boost::posix_time::nanoseconds(GB_CYCLE));

	if (!_handler_cycles)
		_handler_cycles = _handler.doInterrupt();
/*
	if (!_checkInterrupts())
		_checkCPU();

	_checkLCD();
*/
	// wait for chrono here
	t.wait();
	_clockCycle();
}

void GameBoy::_wireComponents()
{
	// TODO: Init all here
	p.setMemory(&m);
	p.setHandler(&_handler);
	// lcd.setMemory(&m);
	_handler.setMemory(&m);
}

void GameBoy::_clockCycle()
{
	// Decrease all pending timers
	if (_handler_cycles) --_handler_cycles;
	if (_cpu_cycles) --_cpu_cycles;
	if (_lcd_cycles) --_lcd_cycles;
}


void GameBoy::_resetComponents()
{
	// TODO Reset components here
}

GameBoy::GameBoy()
{
	_wireComponents();
}

void GameBoy::changeGame(uint8_t * mem, size_t s)
{
	//TODO: memory copies the content of the pointer.
	//_resetComponents();
	//m.setCartridge(mem, s);
}
