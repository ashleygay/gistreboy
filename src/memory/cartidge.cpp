#include <cartridge.hpp>

Cartridge::Cartridge(uint8_t *cart)
{
 /*
  std::ifstream infile;
  infile.open("roms/boot.gb");
  uint8_t byte = 0
  while (!infile.eof())
  {
    infile >> byte;
    if (infile.fail())
      break;
    boot_rom.push_back(byte);
  }
 */
  rom(cart);
  for (uint16_t i = 0x134; i < 0x144; i++)
    name.push_back((char)rom[i]);

  type = rom[0x147];

  switch (type)
  {
  case 0x00 :
    mbc = 0;
    break;
  case 0x01 :
    mbc = 1;
    break;
  case 0x02 :
    mbc = 1;
    has_ram = true;
    break;
  case 0x03 :
    mbc = 1;
    has_ram = true;
    has_battery = true;
    break;
  case 0x05 :
    mbc = 2;
    break;
  case 0x06 :
    mbc = 2;
    has_battery = true;
    break;
  case 0x08 :
    mbc = 0;
    has_ram = true;
    break;
  case 0x09 :
    mbc = 0;
    has_ram = true;
    has_battery = true;
    break;
  case 0x0B :
    mbc = 4;
    break;
  case 0x0C :
    mbc = 4;
    has_ram = true;
    break;
  case 0x0D :
    mbc = 4;
    has_ram = true;
    has_battery = true;
    break;
  case 0x0F :
    mbc = 3;
    has_timer = true;
    has_battery = true;
    break;
  case 0x10 :
    mbc = 3;
    has_ram = true;
    has_timer = true;
    has_battery = true;
    break;
  case 0x11 :
    mbc = 3;
    break;
  case 0x12 :
    mbc = 3;
    has_ram = true;
    break;
  case 0x13 :
    mbc = 3;
    has_ram = true;
    has_battery = true;
    break;
  case 0x19 :
    mbc = 5;
    break;
  case 0x1A :
    mbc = 5;
    has_ram = true;
    break;
  case 0x1B :
    mbc = 5;
    has_ram = true;
    has_battery = true;
    break;
  case 0x1C :
    mbc = 5;
    has_rumble = true;
    break;
  case 0x1D :
    mbc = 5;
    has_rumble = true;
    has_ram = true;
    break;
  case 0x1E :
    mbc = 5;
    has_rumble = true;
    has_ram = true;
    has_battery = true;
    break;
  default :
    break;
  }

  uint8_t size_rom = rom[0x148];
  switch(size)
  {
  case 0x00 :
    rom_size = 32000;
    break;
  case 0x01 :
    rom_size = 64000;
    break;
  case 0x02 :
    rom_size = 128000;
    break;
  case 0x03 :
    rom_size = 256000;
    break;
  case 0x04 :
    rom_size = 512000;
    break;
  case 0x05 :
    rom_size = 1000000;
    break;
  case 0x06 :
    rom_size = 2000000;
    break;
  case 0x07 :
    rom_size = 4000000;
    break;
  case 0x52 :
    rom_size = 1100000;
    break;
  case 0x53 :
    rom_size = 1200000;
    break;
  case 0x54 :
    rom_size = 1500000;
    break;
  default :
    break;
  }

  if (has_ram)
  {
    size_t size_ram = rom[0x149];
    switch(size_ram)
    {
    case 0x00 :
      if (mbc == 2)
        ram_size = 256;
      else
        ram_size = 0;
      break;
    case 0x01 :
      ram_size = 2000;
      break;
    case 0x02 :
      ram_size = 8000;
      break;
    case 0x03 :
      ram_size = 32000;
      break;
    default :
      break;
    }
    for (size_t i = 0; i < ram_size; i++)
      ram.push_back(0x00);
  }
}

uint8_t Cartridge::read(uint16_t address)
{
  return 0x42;
}

void Cartridge::write(uint16_t address, uint8_t byte)
{

}

bool Cartridge::ram_enable()
{
  return ram_enable;
}

bool Cartridge::rom_ram_mode()
{
  return rom_ram_mode;
}

bool Cartridge::has_ram()
{
  return has_ram;
}

bool Cartridge::has_battery()
{
  return has_battery;
}

bool Cartridge::has_timer()
{
  return has_timer;
}

bool Cartridge::has_rumble()
{
  return has_rumble;
}

bool Cartridge::has_boot()
{
  return has_boot;
}
