/*
 * File : gameboy.cpp
 *
 * File created by : Corentin Gay
 * File was created at : 08/10/2017
 */

#include <gameboy.hpp>


GameBoy::GameBoy(): _mem(p), _lcd(_mem), _timers(_mem)
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
	int _cpu_cycles = p.step();
	_lcd.step(_cpu_cycles);
	_timers.step(_cpu_cycles);
	_checkKeys();
}

void GameBoy::_wireComponents()
{
	p.setMemory(&_mem);
}

void GameBoy::_checkKeys()
{
	uint8_t reg = _mem.get_joypad();
	uint8_t keys = getAtomic();
	uint8_t buttons = keys >> 4; // The highest bits are the buttons.
	uint8_t pad = keys & 0x0F;

	// We keep only the select bits.
	keys &= 0b00110000;

	// If button is pressed but line is not selected
	// we dont interrupt
	if ((keys & (1 << 5))) { // Bit 5 is set we 'or' the button bits
		keys |= buttons;
		_interruptJOYPAD();
	}

	if ((keys & (1 << 4))) { // Bit 4 is set we 'or' the pad bits
		keys |= pad;
		_interruptJOYPAD();
	}

	// Write modified register to 0xFF00
	setAtomic(keys);
}

void GameBoy::_interruptJOYPAD()
{
	_mem.set_interrupt_flag(Memory::Interrupt::JOYPAD);
}

void GameBoy::_resetComponents()
{
	//TODO: reset the CPU :)
	_mem.reset();
}

void GameBoy::changeGame(uint8_t *mem)
{
	_resetComponents();
	_mem.change_game(mem);
}

void GameBoy::setAtomic(uint8_t value)
{
  	_keys.store(value);
}

uint8_t GameBoy::getAtomic()
{
  	return _keys.load();
}

void GameBoy::setJoypadInterrupt()
{
  	_mem.set_interrupt_flag(Interrupt::JOYPAD);
}
