#include <video.hpp>
#include <bitset>

Video::Video(Processor& proc,
	std::vector<std::pair<uint16_t, uint16_t>> range) :
	MemoryObject(range),
	_proc(proc)
{
	video_memory.fill(0);
}

uint8_t Video::read(uint16_t address)
{
	return video_memory[address];
}

void Video::write(uint8_t byte, uint16_t address)
{
	if (address == 0xFF40)
	{
		uint16_t beg_src = (byte << 8);
		uint16_t end_src = (byte << 8) | 0x9F;

		dma_transfer(beg_src, end_src);
		
	}

	video_memory[address] = byte;
}

void Video::dma_transfer(uint16_t beg_src, uint16_t end_src)
{
	uint16_t beg_dest = 0xFE00;

	uint16_t inc_src = beg_src;
	uint16_t inc_dest = beg_dest;
	uint8_t byte = 0;

	while (inc_src <= end_src)
	{
		byte = _proc._read(inc_src);
		_proc._write(byte, inc_dest);
		++inc_src;
		++inc_dest;
	}
}

bool Video::can_read(uint16_t address)
{
	//FIXME
	return true;
}

bool Video::can_write(uint8_t byte, uint16_t address)
{
	//FIXME
	return true;
}

void Video::set_accessible(bool accessible)
{
	//FIXME
}

uint8_t Video::get_lcd_control()
{
	return video_memory[0xFF40];
}

uint8_t Video::get_lcd_status()
{
	return video_memory[0xFF41];
}

uint8_t Video::get_scrolly()
{
	return video_memory[0xFF42];
}

uint8_t Video::get_scrollx()
{
	return video_memory[0xFF43];
}

uint8_t Video::get_ly()
{
	return video_memory[0xFF44];
}

uint8_t Video::get_lyc()
{
	return video_memory[0xFF45];
}

uint8_t Video::get_wy()
{
	return video_memory[0xFF4A];
}

uint8_t Video::get_wx()
{
	return video_memory[0xFF4B];
}

uint8_t Video::get_bgp()
{
	return video_memory[0xFF47];
}

uint8_t Video::get_obp0()
{
	return video_memory[0xFF48];
}

uint8_t Video::get_obp1()
{
	return video_memory[0xFF49];
}
