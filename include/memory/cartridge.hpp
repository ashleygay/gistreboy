#pragma once

#include <vector>
#include <array>
#include <string>
#include <fstream>
#include <memoryobject.hpp>

class Cartridge : public MemoryObject {

public :

	Cartridge() {}

	Cartridge(Processor* proc,
		  std::vector<std::pair<uint16_t, uint16_t>> rang,
		  uint8_t *cart);
  
	uint8_t read(uint16_t address);
	void write(uint16_t address, uint8_t byte);  

	bool check_permissions_read(uint16_t address);
	bool check_permissions_write(uint16_t address, uint8_t byte);

	bool ram_enable();
	bool has_boot();

	bool rom_ram_mode();
	bool has_ram();
	bool has_battery();
	bool has_timer();
	bool has_rumble();

private :

	uint8_t get_current_rom_bank();
	uint8_t get_current_ram_bank();

	/*the actual assembly of the cartridge separated in banks of 32kB */
	std::array<uint8_t, 2097152> rom;

  /* a program inside the gameboy that boots the machine
     and jumps to the location of the animated sequence
     inside the rom */

	//This array has been generated with the xd utility tool.
	std::array<uint8_t, 256> boot_rom = { {
		49,254,255,175,33,255,159,50,203,124,32,251,33,38,255,14,17,62,128,50,
		226,12,62,243,226,50,62,119,119,62,252,224,71,17,4,1,33,16,128,26,205,
		149,0,205,150,0,19,123,254,52,32,243,17,216,0,6,8,26,19,34,35,5,32,249,
		62,25,234,16,153,33,47,153,14,12,61,40,8,50,13,32,249,46,15,24,243,103,
		62,100,87,224,66,62,145,224,64,4,30,2,14,12,240,68,254,144,32,250,13,
		32,247,29,32,242,14,19,36,124,30,131,254,98,40,6,30,193,254,100,32,6,
		123,226,12,62,135,226,240,66,144,224,66,21,32,210,5,32,79,22,32,24,203,
		79,6,4,197,203,17,23,193,203,17,23,5,32,245,34,35,34,35,201,206,237,102,
		102,204,13,0,11,3,115,0,131,0,12,0,13,0,8,17,31,136,137,0,14,220,204,
		110,230,221,221,217,153,187,187,103,99,110,14,236,204,221,220,153,159,
		187,185,51,62,60,66,185,165,185,165,66,60,33,4,1,17,168,0,26,19,190,32,
		254,35,125,254,52,32,245,6,25,120,134,35,5,32,251,134,32,254,62,1,224,
		80
	} };

  /* the type of the cartidge see manual */
  uint8_t type = 0;

  /* the MBC of the cartridge, chip that will extend address space,
     no MBC is a simple 32kb cartidge like Tetris
     no MBC is 0, MM01 is 4 */
  int mbc = 0;

  /* the internal ram of the cartridge */
  std::array<uint8_t, 32768> ram;

  size_t rom_size = 0;
  size_t ram_size = 0;

  uint8_t rom_bank_number = 0;
  uint8_t ram_bank_number = 0; /* can be upper 2 bit of rom_bank_number */

  bool ram_enable_ = false;
  bool rom_ram_mode_ = false; /* false if rom mode, true if ram mode */

  bool has_ram_ = false;
  bool has_battery_ = false;
  bool has_timer_ = false;
  bool has_rumble_ = false;

  bool has_boot_ = false; /* true when boot rom is finished */

  std::string name;

};
