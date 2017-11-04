#include <video.hpp>

class VideoModule
{

public:

	VideoModule(Video *video) : video_mem(video) {}

	/*render the tile pixels for the current line*/
	void render_tiles(int current_line);
	/*render the sprites pixels for the current line*/
	void render_sprites(int current_line);

	/*
	   map of pixel of the current screen 
	   0 = White
	   1 = Light Gray
	   2 = Dark Gray
	   3 = Black
        */

	std::array<std::array<int,144>, 160> pixels;

private:

	int16_t get_tile_num(uint16_t tilemap_addr, uint8_t x, uint8_t y,
			     bool is_signed);

	uint16_t get_tile_address(uint16_t tile_addr, int16_t tilenum,
				  bool is_signed);

	uint8_t get_color_id(uint16_t tile_addr, uint8_t x, uint8_t y);

	int get_color(uint8_t id, uint8_t palette);

	Video *video_mem;

};
