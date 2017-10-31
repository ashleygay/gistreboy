/*
 * File : gameboy.hpp
 *
 * File created by : Corentin Gay
 * File was created the : 08/10/2017
 */

#pragma once

#include <debug.hpp>
#include <interrupthandler.hpp>
#include <processor.hpp>
#include <memory.hpp>

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

		void changeGame(uint8_t * mem, size_t s);

		bool isRunning() {return _running;}
		void stop() {_running = false;}
		void start() {_running = true;}

	private:
		void _resetComponents();
		void _wireComponents();
		void _clockCycle();

	private:
		//TODO:	Each class is actually inside a Component class that
		// handles each processor/clock/memory/lcd.

		Processor p;
		Memory m;
		//LCD lcd;


		// Used to handle periodic interrupts or interrupts provided by
		// the software (joypad inputs)
		InterruptHandler _handler;

		int _handler_cycles = 0;
		int _cpu_cycles = 0;
		int _lcd_cycles = 0;

		boost::asio::io_service io;

		std::atomic<bool> _running{false};
};
