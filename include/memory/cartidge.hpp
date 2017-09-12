#pragma once

#include <vector>
#include <string>

class Cartridge {

public :
  Cartridge(char *cart);
  
  uint8_t read(uint16_t address);
  void write(uint16_t address, uint8_t byte);  

  bool ram_enable();
  bool has_boot();

  bool rom_ram_mode();
  bool has_ram();
  bool has_battery();
  bool has_timer();
  bool has_rumble();

private :

  /* the actual assembly of the cartridge */
  std::vector<uint8_t> rom;

  /* a program inside the gameboy that boots the machine
     and jumps to the location of the animated sequence
     inside the rom */
  std::vector<uint8_t> boot_rom;

  /* the type of the cartidge see manual */
  uint8_t type = 0;

  /* the MBC of the cartridge, chip that will extend address space,
     no MBC is a simple 32kb cartidge like Tetris
     no MBC is 0, MM01 is 4 */
  int mbc = 0;

  /* the internal ram of the cartridge */
  std::vector<uint8_t> ram;

  size_t rom_size = 0;
  size_t ram_size = 0;

  uint8_t rom_bank_number = 0;
  uint8_t ram_bank_number = 0; /* can be upper bit of rom_bank_number */

  bool ram_enable = false;
  bool rom_ram_mode = false; /* false if rom mode, true if ram mode */

  bool has_ram = false;
  bool has_battery = false;
  bool has_timer = false;
  bool has_rumble = false;

  bool has_boot = false; /* true when boot rom is finished */

  std::string name;

};
