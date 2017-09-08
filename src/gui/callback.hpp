#pragma once
#include <gtk/gtk.h>
#include <debug.hpp>
#include <iostream>
#include <unordered_map>
#include <open_button_helper.hpp>


using checksum_fun = int (*)(const char *, off_t);
using str_to_str = std::unordered_map<std::string, std::string>;

void NYI(GtkWidget * b, gpointer user_data);
void open_button_callback(GtkWidget * b, gpointer user_data);
void quit_callback(GtkWidget * w, gpointer data);
gboolean draw_callback(GtkWidget * w, cairo_t *cr, gpointer user_data);
int trigger_draw(GtkWidget * area, GdkFrameClock * c, gpointer user_data);
