/*
 * File : gameboy.hpp
 *
 * File created by : Corentin Gay
 * File was created the : 08/10/2017
 */

#pragma once

#include <debug.hpp>
#include <processor.hpp>
#include <memory.hpp>
#include <processor.hpp>
#include <memory.hpp>
#include <lcd.hpp>

#include <gtk/gtk.h>
#include <iostream>
#include <array>
#include <string>
#include <chrono>
#include <thread>
#include <future>
#include <atomic>
#include <boost/asio.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

#define GB_CYCLE 238

class GameBoy
{
	public:
		GameBoy();

		// Execute a single step loop of the emulator
		void step();

		void changeGame(uint8_t *mem);

		bool isRunning() {return _running;}
		void stop() {_running = false;}

		// Tries to start the gameboy, if memory not set
		// returns false.
		bool readyToLaunch();

	private:
		void _resetComponents();
		void _wireComponents();
		void _clockCycle();

	private:
		Processor p;
		Memory _mem;

		LCD _lcd;
		int _handler_cycles = 0;
		int _cpu_cycles = 0;
		int _lcd_cycles = 0;

		boost::asio::io_service io;

		std::atomic<bool> _running{false};
};
