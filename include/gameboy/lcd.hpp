/*
 * File : lcd.hpp
 *
 * File created by : Corentin Gay
 * File was created at : 01/12/2017
 */

#pragma once

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



#include <interrupthandler.hpp>

class LCD
{
	public:
		LCD(InterruptHandler &it, Memory &mem);
		int step();

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
		//std::bitset<8>& _CONTROL;
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
	//TODO: maybe use a reference with a bitset, it would be nice
		//std::bitset<8>& _STAT;


	private:
		InterruptHandler &_it;
		Video &_video;
};
