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

#ifdef BENCH_STREAM
	BENCH_STREAM << "Clock Period "
	<< std::chrono::high_resolution_clock::period::den
	<< std::endl;
#endif
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
#ifdef BENCH_STREAM
	auto start_time = std::chrono::high_resolution_clock::now();
#endif

	if (!_cpu_cycles) {
		_cpu_cycles = p.step();
		_lcd.step(_cpu_cycles);
	}

#ifdef BENCH_STREAM
	auto end_time = std::chrono::high_resolution_clock::now();
	BENCH_STREAM << "Period lasted "
	<< std::chrono::duration_cast<std::chrono::nanoseconds>(end_time
					- start_time).count()
	<< " nanoseconds" << std::endl;
	BENCH_STREAM << "Current CPU cycle " << _cpu_cycles << std::endl;
#endif
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

void GameBoy::setatomic(uint8_t value)
{
  	_atomic.store(value);
}

uint8_t GameBoy::getatomic()
{
  	return _atomic.load();
}  

void GameBoy::update_memory(uint8_t byte, uint16_t address)
{
  	_mem.write(byte, address);
}

void GameBoy::set_interrupt_joypad()
{
  	_mem.set_interrupt_flag(Interrupt::JOYPAD);
}
