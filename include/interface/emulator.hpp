/*
 * File : emu_interface.hpp
 *
 * This class is used by the GUI to communicate with the emulator itself
 # This class now handles both the interfacing and the threading.
 *
 * File created by : Corentin Gay
 * File was created the : 16/09/2017
 */

#pragma once


#include <gameboy.hpp>
#include <debug.hpp>

#include <iostream>
#include <array>
#include <string>
#include <chrono>
#include <thread>
#include <unistd.h>

class Emulator
{
	public:
		static Emulator& getInstance()
			{static Emulator emu; return emu;}

	public:
		// Called when the user changes the game
		// 	mem is the content of the file
		// 	s is the size of the file
		void changeCartridge(uint8_t *data);

		// Returns a buffer ready to be displayed directly on screen
		const uint8_t * getRenderedPixels();

		// Starts the emulator with the current memory address
		void start();

		// Stops the currently running emulator
		void stop();

	private:
		// Renders the VRAM onto the pixel buffer
		void _renderPixels();

		Emulator();

	private:
		static void mainLoop(GameBoy& gb);

	public:
		// Deleted operators here
		Emulator(Emulator const &) = delete;
		void operator=(Emulator const &) = delete;

	private:
		GameBoy gb;
		std::future<void> _future;

		uint8_t _pixels[600 * 400];
		uint8_t * _mem = NULL;
		size_t _s;
};
