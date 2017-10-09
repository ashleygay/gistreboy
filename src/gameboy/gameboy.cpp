/*
 * File : gameboy.cpp
 *
 * File created by : Corentin Gay
 * File was created at : 08/10/2017
 */

#include <gameboy.hpp>



void GameBoy::step()
{
	// Priority order:
	// 	Interrupts
	// 	Next Instruction
}

void GameBoy::_wireComponents()
{
	// TODO: Init all here
	// p.setMemory(&m);
	// c.setProc(&p);
	// lcd.setMemory(&m);
	// ip.setProc(&p);
	// ip.setMemory(&m);
}

void GameBoy::_resetComponents()
{
	//Recreate all components probably
}

GameBoy::GameBoy()
{
	_wireComponents();
}

void GameBoy::changeGame(uint8_t * mem, size_t s)
{
	//TODO: memory copies the content of the pointer.
	//_resetComponents();
	//m.setCartridge(mem, s);
}
