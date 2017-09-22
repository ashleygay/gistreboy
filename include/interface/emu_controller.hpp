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

#include <gtk/gtk.h>
#include <iostream>
#include <array>
#include <string>
#include <chrono>
#include <thread>
#include <future>
#include <atomic>



// This class will contain the processor and the clock, and then we only have on
// singleton, EmuInterface

class DummyProcessor
{

	public:
		bool isRunning() {return _running;}
		void stop() {_running = false;}
		void start() {_running = true;}

	private:
		std::atomic<bool> _running{false};
};

class EmuController
{
	using Processor = DummyProcessor;
	public:
		EmuController();
		void startEmulator();
		void stopEmulator();
	private:
		//static void mainLoop(Processor &p, Clock &c);
		static void mainLoop(Processor& p);
	private:
		//TODO: future here
		std::future<void> _future;
		Processor _p;
		//Clock c;

		// Contains error messages.
		std::array<std::string, 2> _errors;
};
