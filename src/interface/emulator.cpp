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

void Emulator::mainLoop(GameBoy& gb)
{
	//TODO: Display an error message if not ready
	if (!gb.readyToLaunch()) {
		std::cout << "Load a game first." << std::endl;
		return;
	}

	while(gb.isRunning()) {
		gb.step();
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
		gb.stop();
		_future.get();
	}
	catch (const std::exception&) {
	}
}

void Emulator::key_press(Key k)
{
	display_key(k);

	auto keys = gb.getAtomic();
	keys |= (1 << k);
	gb.setAtomic(keys);
}

void Emulator::key_release(Key k)
{
	display_key(k);

	auto keys = gb.getAtomic();
	keys &= ~(1 << k);
	gb.setAtomic(keys);
}

void Emulator::changeCartridge(uint8_t *data)
{
	stop();
	gb.changeGame(data);
}
