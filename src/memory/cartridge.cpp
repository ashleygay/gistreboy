#include <cartridge.hpp>

Cartridge::Cartridge(std::vector<std::pair<uint16_t, uint16_t>> range,
			uint8_t *cart) :
			MemoryObject(range)
{
	rom.fill(0);
  	ram.fill(0);

	for (uint16_t i = 0x134; i < 0x144; i++)
		name.push_back((char)cart[i]);

	type = cart[0x147];

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
		has_ram_ = true;
		break;
	case 0x03 :
		mbc = 1;
		has_ram_ = true;
		has_battery_ = true;
		break;
	case 0x05 :
		mbc = 2;
		break;
	case 0x06 :
		mbc = 2;
		has_battery_ = true;
		break;
	case 0x08 :
		mbc = 0;
		has_ram_ = true;
		break;
	case 0x09 :
		mbc = 0;
		has_ram_ = true;
		has_battery_ = true;
		break;
	case 0x0B :
		mbc = 4;
		break;
	case 0x0C :
		mbc = 4;
		has_ram_ = true;
		break;
	case 0x0D :
		mbc = 4;
		has_ram_ = true;
		has_battery_ = true;
		break;
	case 0x0F :
		mbc = 3;
		has_timer_ = true;
		has_battery_ = true;
		break;
	case 0x10 :
		mbc = 3;
		has_ram_ = true;
		has_timer_ = true;
		has_battery_ = true;
		break;
	case 0x11 :
		mbc = 3;
		break;
	case 0x12 :
		mbc = 3;
		has_ram_ = true;
		break;
	case 0x13 :
		mbc = 3;
		has_ram_ = true;
		has_battery_ = true;
		break;
	case 0x19 :
		mbc = 5;
		break;
	case 0x1A :
		mbc = 5;
		has_ram_ = true;
		break;
	case 0x1B :
		mbc = 5;
		has_ram_ = true;
		has_battery_ = true;
		break;
	case 0x1C :
		mbc = 5;
		has_rumble_ = true;
		break;
	case 0x1D :
		mbc = 5;
		has_rumble_ = true;
		has_ram_ = true;
		break;
	case 0x1E :
		mbc = 5;
		has_rumble_ = true;
		has_ram_ = true;
		has_battery_ = true;
		break;
	default :
		break;
	}

	uint8_t size_rom = cart[0x148];
	switch(size_rom)
	{
	case 0x00 :
		rom_size = 32768;
		break;
	case 0x01 :
		rom_size = 65536;
		break;
	case 0x02 :
		rom_size = 131072;
		break;
	case 0x03 :
		rom_size = 262144;
		break;
	case 0x04 :
		rom_size = 524288;
		break;
	case 0x05 :
		rom_size = 1048576;
		break;
	case 0x06 :
		rom_size = 2097152;
		break;
	case 0x07 :
		rom_size = 4194304;
		break;
	case 0x52 :
		rom_size = 1179648;
		break;
	case 0x53 :
		rom_size = 1310720;
		break;
	case 0x54 :
		rom_size = 1572864;
		break;
	default :
		break;
	}

	for (size_t i = 0; i < rom_size; i++)
		rom[i] = cart[i];

	if (has_ram_)
	{
		size_t size_ram = cart[0x149];
		switch(size_ram)
		{
		case 0x00 :
			if (mbc == 2)
				ram_size = 256;
			else
				ram_size = 0;
			break;
		case 0x01 :
			ram_size = 2048;
			break;
		case 0x02 :
			ram_size = 8192;
			break;
		case 0x03 :
			ram_size = 32768;
			break;
		default :
			break;
    		}
  	}
}

uint8_t Cartridge::read(uint16_t address)
{
	if (addr_in_range(address, 0x00, 0x3FFF))
	{
		if (address == 0x100)
			has_boot_ = true;
		if (addr_in_range(address, 0x00, 0xFF) && !has_boot_)
			return boot_rom[address];
		else
			return rom[address];
	}

	else if (addr_in_range(address, 0x4000, 0x7FFF))
	{
		if (mbc == 0)
			return rom[address];
		else
			return rom[address + get_current_rom_bank()*16384];
	}

	else if (addr_in_range(address, 0xA000, 0xBFFF))
		return ram[address + get_current_ram_bank()*8192 - 0xA000];

	return 0;
}

void Cartridge::write(uint16_t address, uint8_t byte)
{
	if (addr_in_range(address, 0xA000, 0xBFFF))
		ram[address + get_current_ram_bank()*8192 - 0xA000] = byte;

	else if (addr_in_range(address, 0x00, 0X1FFF))
		ram_enable_ = ((byte & 0x0F) == 0x0A);

	else if (addr_in_range(address, 0x2000, 0x3FFF))
	{
		if (byte > 0x1F)
			rom_bank_number = 0x01;
		else if (byte == 0x00 || byte == 0x20 || byte == 0x40
			 || byte == 0x60)
			rom_bank_number = byte + 1;
		else
			rom_bank_number = byte;
	}

	else if (addr_in_range(address, 0x4000, 0x5FFF))
		ram_bank_number = byte;
	else if (addr_in_range(address, 0x6000, 0x7FFF))
	{
		if (byte == 0x00)
			rom_ram_mode_ = false;
		else if (byte == 0x01)
			rom_ram_mode_ = true;
	}

}

bool Cartridge::can_read(uint16_t address)
{
	return true;
}

bool Cartridge::can_write(uint16_t address, uint8_t byte)
{
	return true;
}

uint8_t Cartridge::get_current_rom_bank()
{
	if (rom_ram_mode_)
		return rom_bank_number;
	else
		return (ram_bank_number << 5)+rom_bank_number;
		
}

uint8_t Cartridge::get_current_ram_bank()
{
	if (rom_ram_mode_)
		return ram_bank_number;
	else
		return 0;
}

bool Cartridge::ram_enable()
{
  return ram_enable_;
}

bool Cartridge::rom_ram_mode()
{
  return rom_ram_mode_;
}

bool Cartridge::has_ram()
{
  return has_ram_;
}

bool Cartridge::has_battery()
{
  return has_battery_;
}

bool Cartridge::has_timer()
{
  return has_timer_;
}

bool Cartridge::has_rumble()
{
  return has_rumble_;
}

bool Cartridge::has_boot()
{
  return has_boot_;
}
