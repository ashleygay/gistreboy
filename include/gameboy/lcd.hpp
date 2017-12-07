/*
 * File : lcd.hpp
 *
 * File created by : Corentin Gay
 * File was created at : 01/12/2017
 */

#pragma once

#include <array>

class Memory;

#include <memory.hpp>
#include <video.hpp>
#include <video_module.hpp>

class LCD
{

/*
<===================================>
	LCD CONTROLLER STATES
<===================================>

 Different status of the LCD controller:

 Mode 0: The LCD controller is in the H-Blank period and
         the CPU can access both the display RAM (8000h-9FFFh)
         and OAM (FE00h-FE9Fh)

 Mode 1: The LCD controller is in the V-Blank period (or the
         display is disabled) and the CPU can access both the
         display RAM (8000h-9FFFh) and OAM (FE00h-FE9Fh)

 Mode 2: The LCD controller is reading from OAM memory.
         The CPU <cannot> access OAM memory (FE00h-FE9Fh)
         during this period.

 Mode 3: The LCD controller is reading from both OAM and VRAM,
         The CPU <cannot> access OAM and VRAM during this period.
         CGB Mode: Cannot access Palette Data (FF69,FF6B) either.

 Mode 2  2_____2_____2_____2_____2_____2___________________2____
 Mode 3  _33____33____33____33____33____33__________________3___
 Mode 0  ___000___000___000___000___000___000________________000
 Mode 1  ____________________________________11111111111111_____
*/
	enum LCDState {Mode0, Mode1, Mode2, Mode3};

	struct State
	{

		LCDState state = LCDState::Mode0;

		// Represents the number of clock cycles
		// that we are spending in that mode.
		int duration = 0;

		bool can_access_VRAM() const
		{return state != LCDState::Mode3;}

		bool can_access_OAM() const
		{return (state != LCDState::Mode2
			&& state != LCDState::Mode3);}

	};


	public:
		LCD(Memory &mem);

		/*
		 *	This function updates the bitset that are used
		 *	to represent the different registers of the LCD.
		 */

		std::array<std::array<int,144>, 160> pixels;

		void update_variables(int elapsed_time);

		void step(int elapsed_time);

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

		void check_lyc();

		void check_interrupt_stat(int num_bit);

		void draw();

		void draw_scanline();

/*
	<==========================>
		LCD CONTROL
	<==========================>
	 Bit 7 - LCD Display Enable             (0=Off, 1=On)
	 Bit 6 - Window Tile Map Display Select (0=9800-9BFF, 1=9C00-9FFF)
	 Bit 5 - Window Display Enable          (0=Off, 1=On)
	 Bit 4 - BG & Window Tile Data Select   (0=8800-97FF, 1=8000-8FFF)
	 Bit 3 - BG Tile Map Display Select     (0=9800-9BFF, 1=9C00-9FFF)
	 Bit 2 - OBJ (Sprite) Size              (0=8x8, 1=8x16)
	 Bit 1 - OBJ (Sprite) Display Enable    (0=Off, 1=On)
	 Bit 0 - BG/Window Display/Priority     (0=Off, 1=On)
*/
		std::bitset<8> _CONTROL;
/*
	<==========================>
		STAT REGISTER
	<==========================>
	 Bit 6 - LYC=LY Coincidence Interrupt (1=Enable) (Read/Write)
	 Bit 5 - Mode 2 OAM Interrupt         (1=Enable) (Read/Write)
	 Bit 4 - Mode 1 V-Blank Interrupt     (1=Enable) (Read/Write)
	 Bit 3 - Mode 0 H-Blank Interrupt     (1=Enable) (Read/Write)
	 Bit 2 - Coincidence Flag  (0:LYC<>LY, 1:LYC=LY) (Read Only)
	 Bit 1-0 - Mode Flag       (Mode 0-3, see below) (Read Only)
           0: During H-Blank
           1: During V-Blank
           2: During Searching OAM
           3: During Transferring Data to LCD Driver
*/
		std::bitset<8> _STATUS;

		//FIXME: getter for pixels in VideoModule
		// so that we can actually render them in GTK

	private:
		Memory &_mem;
		Video &_video;

		int16_t get_tile_num(uint16_t tilemap_addr, uint8_t x, uint8_t y, bool is_signed);

		uint16_t get_tile_address(uint16_t tile_addr, int16_t tilenum, bool is_signed);

		uint8_t get_color_id(uint16_t tile_addr, uint8_t x, uint8_t y);

		int get_color(uint8_t id, uint8_t palette);

		// Current line that we are rendering
		// 0-154
		int line = 0;

		// Current LCD Mode

		State current_mode;

		// Elapsed time since last mode change

		int clock = 0;

		using StatesArray = std::array<State, 4>;
		const StatesArray states ={{
		{LCDState::Mode0, 207},
		{LCDState::Mode1, 456},
		{LCDState::Mode2, 80},
		{LCDState::Mode3, 169}
		}};
};
