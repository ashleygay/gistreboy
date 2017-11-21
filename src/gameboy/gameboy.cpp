/*
 * File : gameboy.cpp
 *
 * File created by : Corentin Gay
 * File was created at : 08/10/2017
 */

#include <gameboy.hpp>


GameBoy::GameBoy(): m(p)
{
	//TODO: create memory from processor and rom
	_wireComponents();
}

void GameBoy::step()
{
	// Priority order:
	// 	Interrupts
	// 	Next Instruction

	// Start chrono here for a cycle
	sleep(1);
	std::cout << "GAMEBOY STEP" << std::endl;
	boost::asio::deadline_timer t(io,
			boost::posix_time::nanoseconds(GB_CYCLE));

	if (!_handler_cycles)
	 	_handler_cycles = _handler.doInterrupt();

	// If there was no interrupt to service we execute the next instruction
//	if (!_handler_cycles)
//		_cpu_cycles = p.step();
/*
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
	p.setInterruptHandler(&_handler);
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
	//p.reset();
}

void GameBoy::changeGame(uint8_t *mem)
{
	//TODO: memory copies the content of the pointer.
	//_resetComponents();
	m.change_game(mem);
}
