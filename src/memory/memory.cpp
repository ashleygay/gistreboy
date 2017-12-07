#include <memory.hpp>
#include <vector>
#include <utility>
#include <iostream>

Memory::Memory(Processor& proc) : processor(proc),
	       cartridge({std::make_pair(0x00, 0x7FFF),
			  std::make_pair(0xA000, 0xBFFF)}),

	       video(proc, {std::make_pair(0xFF40, 0xFF4B),
			    std::make_pair(0x8000, 0xFE9F),
			    std::make_pair(0xFE00, 0xFE9F)})
{
	memory.fill(0);
}


void Memory::change_game(uint8_t *cart)
{
	cartridge.change_game(cart);
	_ready = true;
}

bool Memory::is_ready()
{
	return _ready;
}

void Memory::reset()
{
	_ready = false;
}

uint8_t Memory::read(uint16_t address)
{
	if (cartridge.has_boot())
	{
		/*for (uint16_t i = 0x8000; i <= 0x8FFF; i++)
		{
			if (video.simple_read(i))
				std::cout << std::hex << i << std::endl;
		}
		for (uint16_t i = 0x8800; i <= 0x97FF; i++)
		{
			if (video.simple_read(i))
				std::cout << std::hex << i << std::endl;
		}*/
		/*for (uint16_t i = 0xFE00; i <= 0xFE9F; i+=4)
		{
			if (video.simple_read(i+2))
			{
				uint16_t tile_address = 0x8000 + video.simple_read(i+2) * 16;
				for (uint16_t j = tile_address; j<= tile_address+16; j++)
				{
					if (video.simple_read(j))
						std::cout << (int)video.simple_read(j) << std::endl;
				}
			}
		}*/
	}
	if (cartridge.isInRange(address))
		return cartridge.read(address);
	else if (video.isInRange(address))
		return video.read(address);
	else
		return memory[address];
}

void Memory::write(uint8_t byte, uint16_t address)
{
	if (cartridge.isInRange(address))
		cartridge.write(byte, address);
	else if (video.isInRange(address))
		video.write(byte, address);
	else
		memory[address] = byte;
}

void Memory::set_interrupt_flag(unsigned int interrupt)
{
	memory[0xFF0F] |= (1 << interrupt);
}

void Memory::reset_interrupt_flag(unsigned int interrupt)
{
	memory[0xFF0F] &= (~(1 << interrupt));
}

uint8_t Memory::get_interrupt_enable()
{
	return memory[0xFFFF];
}

uint8_t Memory::get_interrupt_flags()
{
	return memory[0xFF0F];
}

uint8_t Memory::get_joypad()
{
	return memory[0xFF00];
}

Video& Memory::get_video()
{
	return video;
}

Cartridge& Memory::get_cartridge()
{
	return cartridge;
}
