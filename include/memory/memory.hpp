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
  	void write(uint16_t address, uint8_t byte);

	// Rebuild a cartridge with a new rom
	void change_game(uint8_t *cart);

	//Resets memory values to their default state
	void resetMemory();

	Video& get_video();
	Cartridge& get_cartridge();

	bool is_ready();

	void reset();

private :

	std::array<uint8_t, 0x10000> memory;

	bool _ready = false;

	Processor& processor;
	Cartridge cartridge;
	Video video;
};
