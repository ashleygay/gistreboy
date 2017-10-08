/*
 * File : emu_controller.hpp
 *
 * This class controls the emulator itself starting/stoping it 
 *
 * File created by : Corentin Gay
 * File was created the : 16/09/2017
 */

#pragma once

#include <debug.hpp>
#include <gameboy.hpp>

#include <gtk/gtk.h>
#include <iostream>
#include <array>
#include <string>
#include <chrono>
#include <thread>
#include <future>
#include <atomic>



// This class will contain the gameboy and will start/stop it.
class EmuController
{
	public:
		EmuController();
		void changeGame(uint8_t * mem, size_t s);
		void startEmulation();
		void stopEmulation();
	private:
		static void mainLoop(GameBoy& gb);
	private:
		std::future<void> _future;
		GameBoy gb;
};
