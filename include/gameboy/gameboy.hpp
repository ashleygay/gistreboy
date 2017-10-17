/*
 * File : gameboy.hpp
 *
 * File created by : Corentin Gay
 * File was created the : 08/10/2017
 */

#pragma once

#include <debug.hpp>

#include <gtk/gtk.h>
#include <iostream>
#include <array>
#include <string>
#include <chrono>
#include <thread>
#include <future>
#include <atomic>
#include <interrupthandler.hpp>

class DummyProcessor
{
};

class GameBoy
{
	using Processor = DummyProcessor;
	public:
		GameBoy();

		// Execute a single step loop of the emulator
		void step();

		void changeGame(uint8_t * mem, size_t s);

		bool isRunning() {return _running;}
		void stop() {_running = false;}
		void start () {_running = true;}

	private:
		void _resetComponents();
		void _wireComponents();
	private:
		//TODO:	Each class is actually inside a Component class that
		// handles each processor/clock/memory/lcd.

		//Processor p;
		//Clock c;
		//Memory m;
		//LCD lcd;


		// Used to handle periodic interrupts or interrupts provided by
		// the software (joypad inputs)
		InterruptHandler ip;

		std::atomic<bool> _running{false};
};
