/*
 * File : gui_setup.hpp
 *
 * File created by : Corentin Gay
 * File was created the : 08/09/2017
 */

#pragma once

#include <gtk/gtk.h>

#include <callback.hpp>
#include <open_button_helper.hpp>

void setup_gui(GtkApplication *app);

using callback_ptr = void (*)(GtkWidget*, gpointer);

// TODO: make buttons work on Ubuntu
// They work on archlinux fine

// XMacro to define all the buttons from the interface.
// menuBar or subMenu to choose where the button will be added
#define MENU_SETUP \
	X("Run", run_button_callback, subMenu, NULL) \
	X("Stop", stop_callback, subMenu, new Helper(window))\
	X("Open image file", open_button_callback, subMenu,\
		new OpenButtonHelper(window, {{"access::can-read", "TRUE"}}))
