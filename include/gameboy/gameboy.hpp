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
#include <timer_handler.hpp>

#include <gtk/gtk.h>
#include <iostream>
#include <array>
#include <string>
#include <chrono>
#include <thread>
#include <future>
#include <atomic>

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

		// Functions called by emulator for interacting
		// with the memory to correctly set the joypad lines (FF00)
  		void setAtomic(uint8_t value);
  		uint8_t getAtomic();

		void setJoypadInterrupt();
	private:
		void _resetComponents();
		void _wireComponents();
		void _clockCycle();
		void _checkKeys(uint8_t atomic);
		void _interruptJOYPAD();
	private:
		Processor p;
		Memory _mem;
		LCD _lcd;
		TimerHandler _timers;

		uint8_t _old_keys = 0;
		std::atomic<bool> _running{false};
                std::atomic<uint8_t> _keys;
};
