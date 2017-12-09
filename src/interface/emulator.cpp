/*
 * File : emu_interface.hpp
 *
 * This class is used by the GUI to communicate with the emulator itself
 *
 * File created by : Corentin Gay
 * File was created the : 17/09/2017
 */

#include <emulator.hpp>

Emulator::Emulator()
{
}

const uint8_t * Emulator::getRenderedPixels()
{
	//TODO: if VRAM has been updated, we render again
	// if(_p.vramToUpdate())
		//_renderPixels();
	DEBUG_STREAM << "Getting pixels" << std::endl;
	return _pixels;
}

void Emulator::_renderPixels()
{
	//TODO: update _pixels here

	DEBUG_STREAM << "Rendering..." << std::endl;

	//_p.setNoUpdate();
}

void Emulator::mainLoop(GameBoy& gb)
{
	//TODO: Display an error message if not ready
	if (!gb.readyToLaunch()) {
		DEBUG_STREAM << "Load a game first." << std::endl;
		return;
	}

	while(gb.isRunning()) {
		gb.step();
		gb.update_memory(gb.getatomic(), 0xFF00);
	}
}

void Emulator::start()
{
	if (!gb.isRunning()) {
		_future = std::async(std::launch::async,
			Emulator::mainLoop, std::ref(gb));
	}
	else
		std::cout << "Emulator already running" << std::endl;
}


void Emulator::stop()
{
	try {
		DEBUG_STREAM << "Stopping gameboy" << std::endl;
		gb.stop();
		_future.get();
		DEBUG_STREAM << "Emulator stopped" << std::endl;
	}
	catch (const std::exception&) {
		DEBUG_STREAM << "Emulator is not started" << std::endl;
	}
}

void Emulator::key_press(Key k)
{
	DEBUG_STREAM << "PRESS ";
	display_key(k);
	switch(k)
	  {
	  case Key::A :
	    gb.setatomic(0x21);
	  case Key::B :
	    gb.setatomic(0x22);
	  case Key::START :
	    gb.setatomic(0x28);
	  case Key::SELECT :
	    gb.setatomic(0x24);
	  case Key::LEFT :
	    gb.setatomic(0x12);
	  case Key::RIGHT :
	    gb.setatomic(0x11);
	  case Key::UP :
	    gb.setatomic(0x14);
	  case Key::DOWN :
	    gb.setatomic(0x18);
	  default:
	    gb.setatomic(0x00);
	  } 
	//TODO: notify the gameboy memory
}

void Emulator::key_release(Key k)
{
	DEBUG_STREAM << "RELEASE ";
	display_key(k);
	//TODO: notify the gameboy memory
}

void Emulator::changeCartridge(uint8_t *data)
{
	stop();
	gb.changeGame(data);
}
