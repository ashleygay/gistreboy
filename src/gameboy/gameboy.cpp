/*
 * File : gameboy.cpp
 *
 * File created by : Corentin Gay
 * File was created at : 08/10/2017
 */

#include <gameboy.hpp>


GameBoy::GameBoy(): _mem(p), _lcd(_mem)
{
	//TODO: create memory from processor and rom
	_wireComponents();
}

bool GameBoy::readyToLaunch()
{
	if (_mem.is_ready()) {
		_running = true;
		return true;
	}
	return false;
}

void GameBoy::step()
{
	// Priority order:
	// 	Interrupts
	// 	Next Instruction

	// Start chrono here for a cycle
	//sleep(1);
//	std::cout << "GAMEBOY STEP" << std::endl;
	boost::asio::deadline_timer t(io,
			boost::posix_time::nanoseconds(GB_CYCLE));

	if (!_cpu_cycles)
		_cpu_cycles = p.step();

	_lcd.step(_cpu_cycles);
	// wait for chrono here
	t.wait();
	_clockCycle();
}

void GameBoy::_wireComponents()
{
	p.setMemory(&_mem);
}

void GameBoy::_clockCycle()
{
	// Decrease all pending timers
	if (_cpu_cycles) --_cpu_cycles;
}


void GameBoy::_resetComponents()
{
	_mem.reset();
}

void GameBoy::changeGame(uint8_t *mem)
{
	_resetComponents();
	_mem.change_game(mem);
}
