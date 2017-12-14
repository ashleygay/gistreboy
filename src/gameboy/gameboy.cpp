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

	using namespace std::chrono_literals;
	int atomic = getAtomic();
	if (_old_keys != atomic) {
		_checkKeys(atomic);
		_old_keys = atomic;
	}
	int _cpu_cycles = p.step();
	_lcd.step(_cpu_cycles);
	_timers.step(_cpu_cycles);

	// FIXME: doesnt work, for now
	//std::this_thread::sleep_for(10ns);
	// Wait after each instruction, this works for -O0
	for (int i = 0 ; i < 15; ++i);
}

void GameBoy::_wireComponents()
{
	p.setMemory(&_mem);
}

void GameBoy::_checkKeys(uint8_t atomic)
{
	uint8_t reg = _mem.get_joypad();
	uint8_t keys = atomic;

	uint8_t buttons = keys & 0x0F; // The lowest bits are the buttons.
	uint8_t pad = keys >> 4;

	// We keep only the select bits.
	reg &= 0b00110000;

	//std::cout << "SELECT BITS: " << std::bitset<8>(reg) << std::endl;
	// If button is pressed but line is not selected
	// we dont interrupt
	uint8_t tmp = 0;
	if ((reg & (1 << 5))) { // Bit 5 is set we 'or' the button bits
		tmp |= buttons;
		_interruptJOYPAD();
	}

	if ((reg & (1 << 4))) { // Bit 4 is set we 'or' the pad bits
		tmp |= pad;
		_interruptJOYPAD();
	}
	tmp = (~tmp & 0x0F);
	reg |= tmp;
	//std::cout << "ATOMIC BITS: " << std::bitset<8>(keys) << std::endl;
	//std::cout << "JOYPAD BITS: " << std::bitset<8>(reg) << std::endl;

	// Write modified register to 0xFF00
	_mem.set_joypad(reg);
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
