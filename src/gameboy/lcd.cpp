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


int LCD::step()
{
	update_variables();

	// We update the permissions of the video memory
	_video.set_OAM_accessible(_state_iter->can_access_OAM());
	_video.set_VRAM_accessible(_state_iter->can_access_VRAM());

	// As we enter Mode1, we trigger the VBLANK interrupt
	if (_state_iter->state == LCDState::Mode1)
		_mem.set_interrupt_flag(Memory::Interrupt::VBLANK);

	return _state_iter->duration;
}


void LCD::update_variables()
{
		_CONTROL = _video.get_lcd_control();
		_STAT = _video.get_lcd_status();
		++_state_iter;
		if (_state_iter == states.cend())
			_state_iter = states.cbegin();
}
