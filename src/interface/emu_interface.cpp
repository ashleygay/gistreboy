/*
 * File : emu_interface.hpp
 *
 * This class is used by the GUI to communicate with the emulator itself
 *
 * File created by : Corentin Gay
 * File was created the : 17/09/2017
 */

#include <emu_interface.hpp>

EmuInterface::EmuInterface()
{
}

const uint8_t * EmuInterface::getRenderedPixels()
{
	//TODO: if VRAM has been updated, we render again
	// if(_p.vramToUpdate())
		//_renderPixels();
	DEBUG_STREAM << "Getting pixels" << std::endl;
	return _pixels;
}

void EmuInterface::_renderPixels()
{
	//TODO: update _pixels here

	DEBUG_STREAM << "Rendering..." << std::endl;

	//_p.setNoUpdate();
}

void EmuInterface::startEmulator()
{
	if (!_mem) {
		_controller.changeGame(_mem, _s);
		_controller.startEmulation();
	}
	else
		std::cout << "Cannot start the emulation without a game"
				<< std::endl;
}


void EmuInterface::stopEmulator()
{
	_controller.stopEmulation();
}

void EmuInterface::changeCartridge(uint8_t * mem, size_t s)
{
	stopEmulator();
	// If previously loaded data, we free the pointer
	if (_mem)
		free(_mem);

	_mem = mem;
	_s = s;
}
