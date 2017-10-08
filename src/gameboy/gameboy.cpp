#include <gameboy.hpp>



void GameBoy::step()
{
}

void GameBoy::_wireComponents()
{
	// TODO: Init all here
	// p.setMemory(&m);
	// c.setProc(&p);
	// lcd.setMemory(&m);
	// ip.setProc(&p);
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
