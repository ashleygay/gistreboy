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
	while(gb.isRunning()) {
		gb.step();
	}
}

void Emulator::start()
{
	if (!gb.isRunning()) {
		_future = std::async(std::launch::async,
			Emulator::mainLoop, std::ref(gb));
		gb.start();
	}
	else
		std::cout << "Emulator already running" << std::endl;
}


void Emulator::stop()
{
	try {
		gb.stop();
		_future.wait();
		_future.get(); // Future calls to wait() will be invalid.
		DEBUG_STREAM << "Emulator stopped" << std::endl;
	}
	catch (const std::exception&) {
		DEBUG_STREAM << "Emulator is not started" << std::endl;
	}
}

void Emulator::changeCartridge(FileContent& f)
{
	stop();
	//TODO
	//gb.setCartridge(f.memory);
	start();
}
