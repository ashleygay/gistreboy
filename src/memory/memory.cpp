#include <memory.hpp>
#include <vector>
#include <utility>

Memory::Memory(uint8_t* rom, Processor& proc)
{
	processor = proc;

	std::vector<std::pair<uint16_t, uint16_t>> range_cart;
	range_cart.push_back(std::make_pair(0x00, 0x7FFF));
	range_cart.push_back(std::make_pair(0xA000, 0xBFFF));
	cartridge(proc, rom);

	std::vector<std::pair<uint16_t, uint16_t>> range_video;
	
	video(proc);
	memory.fill(0);
}

uint8_t Memory::read(uint16_t address)
{
	if (cartridge.isInRange(address))
		return cartridge.read(address);
	else if (video.isInRange(address))
		return video.read(address);
	else
		return memory[address];
}

uint8_t Memory::write(uint16_t address, uint8_t byte)
{
	if (cartridge.isInRange(address))
		cartridge.write(address, byte);
	else if (video.isInRange(address))
		video.write(address, byte);
	else
		memory[address] = byte;
}

Video& Memory::get_video()
{
	return video;
}

Cartridge& Memoery::get_cartridge()
{
	return cartridge;
}


