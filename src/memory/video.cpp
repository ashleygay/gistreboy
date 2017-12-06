#include <video.hpp>
#include <sprite.hpp>
#include <bitset>
#include <array>

Video::Video(Processor& proc,
	std::vector<std::pair<uint16_t, uint16_t>> range) :
	MemoryObject(range),
	_proc(proc)
{
	video_memory.fill(0);
}

uint8_t Video::read(uint16_t address)
{
	if (is_accessible(address))
		return video_memory[address];
	else
		return 0;
}

void Video::write(uint8_t byte, uint16_t address)
{
	if (address == 0xFF40)
	{
		uint16_t beg_src = (byte << 8);
		uint16_t end_src = (byte << 8) | 0x9F;

		dma_transfer(beg_src, end_src);
		
	}

	if (is_accessible(address))
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

bool Video::is_accessible(uint16_t address)
{
	if (_is_VRAM(address))
		return _VRAM_accessible;
	if (_is_OAM(address))
		return _OAM_accessible;
	return true;
}


bool Video::can_read(uint16_t address)
{
	return is_accessible(address);
}

bool Video::can_write(uint16_t address)
{
	return is_accessible(address);
}

void Video::set_VRAM_accessible(bool accessible)
{
	_VRAM_accessible = accessible;
}


void Video::set_OAM_accessible(bool accessible)
{
	_OAM_accessible = accessible;
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

bool Video::_is_VRAM(uint16_t address)
{
 	// VRAM (0x8000-0x9FFF)
	return (address <= 0x9FFF && address >= 0x8000);
}

bool Video::_is_OAM(uint16_t address)
{
 	// OAM (0xFE00-0xFE9F)
	return (address <= 0xFE9F && address >= 0xFE00);
}

std::vector<Sprite> Video::get_sprites()
{
	std::vector<Sprite> sprites;
	for (uint16_t i = 0xFE00; i <= 0xFE9F; i+=4)
	{
		Sprite sprite(video_memory[i], video_memory[i+1],
			      video_memory[i+2], video_memory[i+3]);
		sprites.push_back(sprite);
	}
	return sprites;
}
