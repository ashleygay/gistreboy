#include <video.hpp>
#include <bitset>

Video::Video() {
	video_memory.fill(0);
}

uint8_t Video::read(uint16_t address)
{
	return video_memory[address];
}

void Video::write(uint16_t address, uint8_t byte)
{
	if (address == 0xFF40)
	{
		uint16_t beg_src = (byte << 8) + (0x00 << 8);
		uint16_t end_src = (byte << 8) + (0x9F << 8);
		/*processor.dma_transfer(beg_src, end_src, 0xFE00, 0xFE9F);*/	
	}

	video_memory[address] = byte;
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
