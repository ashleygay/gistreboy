/*
 * File : callback.hpp
 *
 * File created by : Corentin Gay
 * File was created the : 08/09/2017
 */

#pragma once
#include <debug.hpp>
#include <open_button_helper.hpp>
#include <emulator.hpp>

#include <gtk/gtk.h>
#include <unordered_map>
#include <iostream>
#include <string>
#include <chrono>
#include <thread>

// Callbacks for NYI buttons, prints a debug message
void NYI(GtkWidget * b, gpointer user_data);

// Callback for buttons that open files
// b : button widget
// user_data : pointer to a allocated OpenButtonHelper class that will be used
// to determine what kinds of file to open and certain operations on it, as well
// as where to set the result buffer
void open_button_callback(GtkWidget * b, gpointer user_data);

void run_button_callback(GtkWidget * b, gpointer user_data);

// Callback for stoping the currently running emulation
void stop_callback(GtkWidget * w, gpointer data);

// Callback that is called as many times as possible per seconds
// TODO: get the buffer to display from memory here
gboolean draw_callback(GtkWidget * w, cairo_t *cr, gpointer user_data);

// Callback that will be called to trigger the draw event on the display surface
int trigger_draw(GtkWidget * area, GdkFrameClock * c, gpointer user_data);

gboolean key_pressed_callback(GtkWidget *widget, GdkEventKey *event);
