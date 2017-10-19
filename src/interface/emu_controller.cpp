/*
 * File : emu_controller.hpp
 *
 * This class controls the emulator itself starting/stoping it
 *
 * File created by : Corentin Gay
 * File was created the : 21/09/2017
 */

#include <emu_controller.hpp>

EmuController::EmuController()
{
}

void EmuController::mainLoop(GameBoy& gb)
{
	while(gb.isRunning()) {
		gb.step();
	}
}

void EmuController::changeGame(uint8_t * mem, size_t s)
{
	gb.changeGame(mem, s);
}

void EmuController::startEmulation()
{
		stopEmulation();
		_future = std::async(std::launch::async,
			EmuController::mainLoop, std::ref(gb));
		gb.start();
}

void EmuController::stopEmulation()
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
