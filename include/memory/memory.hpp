#pragma once

#include <array>
#include <vector>
#include <string>

#include <processor.hpp>
#include <cartridge.hpp>
#include <video.hpp>

// This class abstracts any memory access done by the processor, it will find
// out which type of memory and what it must be done depending on the address

class Memory {

public :
	Memory(Processor& proc);

  	uint8_t read(uint16_t address);
  	void write(uint8_t byte, uint16_t address);

	// Rebuild a cartridge with a new rom
	void change_game(uint8_t *cart);

	//Resets memory values to their default state
	void resetMemory();

	Video& get_video();
	Cartridge& get_cartridge();

	bool is_ready();

	void reset();

	enum Interrupt {VBLANK, STAT, SERIAL, JOYPAD, TIMER};

	// Zeroes the desired interrupt to enable it
	void set_interrupt_flag(Interrupt inter);

	// Set the desired interrupt to 1
	// Called from interrupt handler to "consume" the interrupt
	void reset_interrupt_flag(int interrupt);

	// Get specific values in memory
	uint8_t get_interrupt_flags();
	uint8_t get_interrupt_enable();

private :

	std::array<uint8_t, 0x10000> memory;

	bool _ready = false;

	Processor& processor;
	Cartridge cartridge;
	Video video;
};
