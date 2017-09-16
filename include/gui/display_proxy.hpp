/*
 * File : display_proxy.hpp
 *
 * File created by : Corentin Gay
 * File was created the : 08/09/2017
 */

#pragma once

#include <debug.hpp>
#include <unordered_map>
#include <gtk/gtk.h>


// This class represents a proxy between the video memory and the buffer to
// display. The GUI part uses it to get info on the buffer to  display. It must
// be updated by the emulator. The coding style changes to respect the coding
// style of the component in which it is used.

using area_to_cairo = std::unordered_map<GtkWidget*, cairo_t *>;

class DisplayProxy
{
	public: //Singleton
		static DisplayProxy& getInstance()
		{
			static DisplayProxy instance;
			return instance;
		}
	
		DisplayProxy(const DisplayProxy &) = delete; 
		void operator=(const DisplayProxy &) = delete;

	public: // Used by the GUI.
		void access_buffer(void);

		//TODO: Drawing area and cairo context
		void register_observer(GtkWidget *w, cairo_t * cr);

	public: // Used by the emulator.
		void updateBuffer(void);

		//TODO: temporary input type so far
		void notifyObservers(const char * buffer);

	private:
		DisplayProxy() {}

	private:
		//pointer to video memory
		char * _vmem;
		
		//list of all observers here
		area_to_cairo _observers;

		int _to_update;
};
