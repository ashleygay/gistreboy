#ifndef ROM_HPP
#define ROM_HPP

#include <vector>
#include <string>

class Cartidge {

public :
  Cartidge(const std::string file_name);
  
  void set_types();
  void set_ram();

private :

  /* the actual assembly of the cartidge */
  std::vector<uint8_t> rom;

  /* a program inside the gameboy that boots the machine
     and jumps to the location of the animated sequence
     inside the rom */
  std::vector<uint8_t> boot_rom;

  /* the type of the cartidge see manual */
  int type;

  /* the MBC of the cartidge, chip that will extend address space,
     no MBC is a simple 32kb cartidge like Tetris*/
  int mbc;

  /* the internal ram of the cartidge */
  std::vector<uint8_t> ram;

  int rom_size;
  int ram_size;

  uint8_t rom_bank_number;
  uint8_t ram_bank_number;

  bool has_ram = false;
  bool has_battery = false;
  bool has_timer = false;
  bool has_rumble = false;

  bool ram_enable = false;

}

#endif
