/*
 * File : lcd.cpp
 *
 * File created by : Corentin Gay
 * File was created at : 01/12/2017
 */

#include "lcd.hpp"
#include <iostream>


LCD::LCD(Memory &mem) :
	_mem(mem),
	_video(mem.get_video())
{

}


void LCD::step(int elapsed_time)
{
	update_variables(elapsed_time);

	if (clock >= current_mode.duration)
	{
		clock -= current_mode.duration;
		switch (current_mode.state)
		{
		case LCDState::Mode0 : //HBLANK
			_video.set_ly(_video.get_ly()+1);
			check_lyc();

			if (_video.get_ly() >= 144)
			{
				current_mode = states[1]; //VBLANK
				_mem.set_interrupt_flag(Memory::Interrupt::VBLANK);
				check_interrupt_stat(4);
				draw();
			}
			else
			{
				current_mode = states[2]; //OAM
				check_interrupt_stat(5);
			}
			break;
		case LCDState::Mode1 : //VBLANK
			_video.set_ly(_video.get_ly()+1);
			check_lyc();

			if (_video.get_ly() > 153)
			{
				_video.set_ly(0);
				current_mode = states[2]; //OAM
				check_interrupt_stat(5);
			}
			break;
		case LCDState::Mode2 : //OAM
			current_mode = states[3]; //VRAM
			break;
		case LCDState::Mode3 : //VRAM
			current_mode = states[0]; //HBLANK
			check_interrupt_stat(3);
			draw_scanline();
			break;

		default :
			break;
		}
		_video.set_OAM_accessible(/*current_mode.can_access_OAM()*/true);
		_video.set_VRAM_accessible(/*current_mode.can_access_VRAM()*/true);
		_video.set_lcd_status_mode((uint8_t)current_mode.state);
	}
}

void LCD::draw()
{
	for (int i = 0; i < 160; i++)
	{
		for (int j = 0; j < 144; j++)
		{
			if (pixels[j][i])
				std::cout << pixels[j][i];
			else
				std::cout << ' ';
			
		}
		std::cout << std::endl;
	}
}

void LCD::draw_scanline()
{
	line = _video.get_ly();
	render_tiles(line);
}

void LCD::check_interrupt_stat(int num_bit)
{
	if (_STATUS[num_bit])
		_mem.set_interrupt_flag(Memory::Interrupt::STAT);
}

void LCD::check_lyc()
{
	_STATUS[2] = (_video.get_ly() == _video.get_lyc());
	_video.set_lcd_status((uint8_t)_STATUS.to_ulong());
	check_interrupt_stat(6);
}


void LCD::update_variables(int elapsed_time)
{
	_CONTROL = _video.get_lcd_control();
	_STATUS = _video.get_lcd_status();

	current_mode = states[((uint8_t)(_STATUS.to_ulong()) & 0x03)];

	clock += elapsed_time;
}

void LCD::render_tiles(int current_line)
{

	/*maybe make all these variables attritbutes of the class*/

	uint16_t tiles_address = 0;
	uint16_t tile_map_address = 0;
	bool is_signed = false;
	bool window_display = false;
	uint8_t scrollx = _video.get_scrollx();
	uint8_t scrolly = _video.get_scrolly();
	uint8_t wx = _video.get_wx() - 7;
	uint8_t wy = _video.get_wy();

	uint8_t lcd_control = _video.get_lcd_control();

	if ((lcd_control >> 5) & 1)
		window_display = (current_line >= wy);
	if ((lcd_control >> 4) & 1)
	{
		tiles_address = 0x8000;
		is_signed = false;
	}
	else
	{
		tiles_address = 0x8800;
		is_signed = true;
	}

	if (!window_display)
	{
		if ((lcd_control >> 3) & 1)
			tile_map_address = 0x9c00;
		else
			tile_map_address = 0x9800;
	}
	else
	{
		if ((lcd_control >> 6) & 1)
			tile_map_address = 0x9c00;
		else
			tile_map_address = 0x9800;
	}


	uint8_t y = scrolly + current_line;
	if (window_display)
		y = current_line - wy;

	for (int i = 0; i < 160; i++)
	{
		uint8_t x = i + scrollx;
		if (window_display)
			x = i - wx;

		int16_t tile_num = get_tile_num(tile_map_address, x, y,
						is_signed);
		uint16_t tile_address = get_tile_address(tiles_address,
							 tile_num,
							 is_signed);

		/*if (_mem.get_cartridge().has_boot())
		{
			for (uint16_t i = tile_address; i < tile_address+16; i++)
			{
				if (_video.simple_read(i))
					std::cout << std::hex << tile_address << std::endl;
			}
		}*/

		uint8_t color_id = get_color_id(tile_address, x, y);

		pixels[i][current_line] = get_color(color_id,
						    _video.get_bgp());
		if (_mem.get_cartridge().has_boot())
		{
			if (pixels[i][current_line] != 0
			    && pixels[i][current_line] != 3)
				std::cout << "ah\n";
		}
	}

}

void LCD::render_sprites(int current_line)
{
	std::bitset<8> lcdc(_video.get_lcd_control());
	bool sprite_enable = lcdc[1];
	bool is_8x16 = lcdc[2];

	uint8_t width = 8;
	uint8_t height = (is_8x16) ? 16 : 8;

	std::vector<Sprite> sprites = _video.get_sprites();
	std::vector<Sprite> visible_sprites;

	for (size_t i = 0; i < sprites.size(); i++)
	{
		if (sprites[i].get_x() == 0
		    || sprites[i].get_x() >= 168
		    || sprites[i].get_y() == 0
		    || sprites[i].get_y() >= 160)
			continue;

		if (sprites[i].get_y_pos() > current_line
		    || sprites[i].get_y_pos() + height <= current_line)
			continue;

		visible_sprites.push_back(sprites[i]);
	}

	for (auto it = visible_sprites.begin();
	     it != visible_sprites.end();)
	{
		
	}

	
	
}

int16_t LCD::get_tile_num(uint16_t tilemap_addr, uint8_t x,
				  uint8_t y, bool is_signed)
{
	uint16_t addr = tilemap_addr + (y / 8) * 32 + (x / 8);
	if (is_signed)
		return (int8_t) _video.simple_read(addr);
	else
		return _video.simple_read(addr);
}

uint16_t LCD::get_tile_address(uint16_t tile_addr, int16_t tilenum,
				       bool is_signed)
{
	if (!is_signed)
		return tile_addr + (tilenum * 16);
	else
		return tile_addr + ((tilenum + 128) * 16);
}

uint8_t LCD::get_color_id(uint16_t tile_addr, uint8_t x, uint8_t y)
{
	uint8_t byte1 = _video.simple_read(tile_addr + (y % 8) * 2);
	uint8_t byte2 = _video.simple_read(tile_addr + (y % 8) * 2 + 1);

	uint8_t result = 0;

	uint8_t bit1 = (byte1 >> (7 - (x % 8))) & 1;
	result+= (bit1) ? 2 : 0;
	uint8_t bit2 = (byte2 >> (7 - (x % 8))) & 1;
	result+= (bit2) ? 1 : 0;

	return result;
}

int LCD::get_color(uint8_t id, uint8_t palette)
{
	return ((palette >> (id*2)) & 0x03);
}
