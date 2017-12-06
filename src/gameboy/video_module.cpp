#include <video_module.hpp>
#include <bitset>

void VideoModule::render_tiles(int current_line)
{

	/*maybe make all these variables attritbutes of the class*/

	uint16_t tiles_address = 0;
	uint16_t tile_map_address = 0;
	bool is_signed = false;
	bool window_display = false;
	uint8_t scrollx = video_mem.get_scrollx();
	uint8_t scrolly = video_mem.get_scrolly();
	uint8_t wx = video_mem.get_wx() - 7;
	uint8_t wy = video_mem.get_wy();

	uint8_t lcd_control = video_mem.get_lcd_control();

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

		uint8_t color_id = get_color_id(tile_address, x, y);

		pixels[i][current_line] = get_color(color_id,
						    video_mem.get_bgp());
	}

}

void VideoModule::render_sprites(int current_line)
{
	std::bitset<8> lcdc(video_mem.get_lcd_control());
	bool sprite_enable = lcdc[1];
	bool is_8x16 = lcdc[2];

	uint8_t width = 8;
	uint8_t height = (is_8x16) ? 16 : 8;

	std::vector<Sprite> sprites = video_mem.get_sprites();
	std::vector<Sprite> visible_sprites;

	for (int i = 0; i < sprites.size(); i++)
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

	for (auto& it = visible_sprites.begin();
	     it != visible_sprites.end())
	{
		
	}

	
	
}

int16_t VideoModule::get_tile_num(uint16_t tilemap_addr, uint8_t x,
				  uint8_t y, bool is_signed)
{
	uint16_t addr = tilemap_addr + (y / 8) * 32 + (x / 8);
	if (is_signed)
		return (int8_t) video_mem.read(addr);
	else
		return video_mem.read(addr);
}

uint16_t VideoModule::get_tile_address(uint16_t tile_addr, int16_t tilenum,
				       bool is_signed)
{
	if (is_signed)
		return tile_addr + (tilenum * 16);
	else
		return tile_addr + ((tilenum + 128) * 16);
}

uint8_t VideoModule::get_color_id(uint16_t tile_addr, uint8_t x, uint8_t y)
{
	uint8_t byte1 = video_mem.read(tile_addr + (y % 8) * 2);
	uint8_t byte2 = video_mem.read(tile_addr + (y % 8) * 2 + 1);

	uint8_t bit1 = (byte1 >> (7 - (x % 8))) & 1;
	uint8_t bit2 = (byte2 >> (7 - (x % 8))) & 1;

	return (bit1 << 1) | bit2;
}

int VideoModule::get_color(uint8_t id, uint8_t palette)
{
	int bit1 = (palette >> (2 * id + 1)) & 1;
	int bit2 = (palette >> (2 * id)) & 1;

	return (bit1 << 1) | bit2;
}
