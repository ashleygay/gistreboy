#pragma once

#include <array>
#include <vector>
#include <string>

// This class abstracts any memory access done by the processor, it will find
// out which type of memory and what it must be done depending on the addresses.

class MemoryAccessor {

public :
  MemoryAccessor(char *cart);

  uint8_t read(uint16_t address);
  void write(uint16_t address, uint8_t byte);

private :

  /* ROM : 0000-3FFF / ROM banks : 4000-7FFF / SRAM : A000-BFFF (MBC1) */
  Cartridge cartridge;
  /* VRAM : 8000-9FFF / OAM : FE00-FE9F
     Video I/O Ports */
  Video	video;
  /* WRAM C000-DFFF */
  std::vector<uint8_t> wram;
  /* echo of WRAM E000-FDFF */
  std::vector<uint8_t> echo_ram;
  /* HRAM */
  std::vector<uint8_t>

  /* FEA0-FEFF not used */

  /*Various I/O ports FF00-FF7F , FFFF*/
  

};
