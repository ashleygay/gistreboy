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
	Memory(uint8_t* rom, Processor* proc);

  	uint8_t read(uint16_t address);
  	void write(uint16_t address, uint8_t byte);

	Video& get_video();
	Cartridge& get_cartridge();

private :

	std::array<uint8_t, 0x10000> memory;

	Processor* processor;
	Cartridge cartridge;
	Video video;
};
