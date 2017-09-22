/*
 * File : main.cpp
 *
 * File created by : Corentin Gay
 * File was created at : 08/09/2017
 */

#include <gtk/gtk.h>
#include <gui_setup.hpp>

int main (int argc, char **argv)
{
	GtkApplication * app;
 	int status = 0;

	app = gtk_application_new ("org.gtk.example", G_APPLICATION_FLAGS_NONE);
	g_signal_connect (app, "activate", G_CALLBACK (setup_gui), NULL);

 	status = g_application_run (G_APPLICATION (app), argc, argv);

	return status;
}
