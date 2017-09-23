/*
 * File : emu_interface.hpp
 *
 * This class is used by the GUI to communicate with the emulator itself
 *
 * File created by : Corentin Gay
 * File was created the : 16/09/2017
 */

#pragma once

#include <debug.hpp>
#include <emu_controller.hpp>

#include <iostream>
#include <array>
#include <string>
#include <chrono>
#include <thread>

class EmuInterface
{
	public:
		static EmuInterface& getInstance()
			{static EmuInterface emu; return emu;}

	public:
		// Called when the user changes the game
		// 	mem is the content of the file
		// 	s is the size of the file
		void changeCartridge(uint8_t * mem, size_t s);

		// Returns a buffer ready to be displayed directly on screen
		const uint8_t * getRenderedPixels();

		// Starts the emulator with the current memory address
		void startEmulator();

		// Stops the currently running emulator
		void stopEmulator();

	private:
		// Renders the VRAM onto the pixel buffer
		void _renderPixels();

		EmuInterface();
	public:
		// Deleted operators here
		EmuInterface(EmuInterface const &) = delete;
		void operator=(EmuInterface const &) = delete;

	private:
		//TODO
		//GtkWidget * window; // Used to display errors
		EmuController _controller;
		uint8_t _pixels[600 * 400];
		uint8_t * _mem = NULL;
		size_t _s;
		
};
