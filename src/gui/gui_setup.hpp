#pragma once

#include <gtk/gtk.h>
#include <callback.hpp>
#include <open_button_helper.hpp>

void setup_gui(GtkApplication *app);

using callback_ptr = void (*)(GtkWidget*, gpointer);

#define MENU_SETUP \
	X("Run", NYI, menuBar, NULL) \
	X("Stop", NYI, menuBar, NULL)\
	X("Open image file", open_button_callback, subMenu,\
		new OpenButtonHelper(42, {{"access::can-read", "TRUE"}}))\
	X("Save state", NYI, subMenu, NULL) \
	X("Load state", NYI, subMenu, NULL)
