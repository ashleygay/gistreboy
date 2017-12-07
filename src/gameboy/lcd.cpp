/*
 * File : lcd.cpp
 *
 * File created by : Corentin Gay
 * File was created at : 01/12/2017
 */

#include "lcd.hpp"


LCD::LCD(Memory &mem) :
	_mem(mem),
	_video(mem.get_video())
{

}


void LCD::step(int elapsed_time)
{
	update_variables(elapsed_time);
	// We update the permissions of the video memory

	// As we enter Mode1, we trigger the VBLANK interrupt

	if (clock >= current_mode.duration)
	{
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
				//draw_sdl();
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
			//draw_scanline()
			break;

		default :
			break;
		}
		clock = 0;
		_video.set_OAM_accessible(current_mode.can_access_OAM());
		_video.set_VRAM_accessible(current_mode.can_access_VRAM());
		_video.set_lcd_status_mode((uint8_t)current_mode.state);
	}
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
