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
	_errors = {"Bad error number", "We are number one"};
}

void EmuController::mainLoop(Processor& p)
{
	//TODO: replace by the actual code
	using namespace std::chrono_literals;
	uint16_t i = 0;
	while(p.isRunning()) {
		std::cout << "Executing loop " << i << std::endl;
		std::this_thread::sleep_for(0.1s);
		++i;
	}
}

void EmuController::startEmulator()
{
		stopEmulator();
		_future = std::async(std::launch::async,
			EmuController::mainLoop, std::ref(_p));
		_p.start();
}

void EmuController::stopEmulator()
{
	try {
		_p.stop();
		_future.wait();
		_future.get(); // Future calls to wait() will be invalid.
		DEBUG_PRINT << "Emulator stopped" << std::endl;
	}
	catch (const std::exception&) {
		DEBUG_PRINT << "Emulator is not started" << std::endl;
	}
}
