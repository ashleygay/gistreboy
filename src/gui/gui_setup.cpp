/*
 * File : gui_setup.cpp
 *
 * File created by : Corentin Gay
 * File was created the : 08/09/2017
 */

#include <gui_setup.hpp>

static void create_menu_item_with_callback(const char *name,  GtkWidget * parent,
					callback_ptr callback, Helper* helper)
{
	GtkWidget *b = gtk_menu_item_new_with_label(name);

	g_signal_connect(b, "activate", G_CALLBACK(callback), helper);

    	gtk_menu_shell_append (GTK_MENU_SHELL (parent), b);
}

static void stub_destroy(gpointer data)
{
	(void)data;
}

void setup_gui (GtkApplication *app)
{
	GtkWidget *window;
	GtkWidget *subMenu;
	GtkWidget *menuBar;
	GtkWidget *menuItem;
	GtkWidget *box;
	GtkWidget *area;

	window = gtk_application_window_new(app);
	gtk_window_set_title(GTK_WINDOW (window), "Super Gistre Boy");
	gtk_window_set_default_size(GTK_WINDOW (window), 600, 400);

	menuItem = gtk_menu_item_new_with_label("Menu");

	area = gtk_drawing_area_new();
	gtk_widget_set_size_request (area, 600, 400);
	subMenu = gtk_menu_new();
	menuBar = gtk_menu_bar_new();
	box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);

	gtk_menu_shell_append(GTK_MENU_SHELL (menuBar), menuItem);

	#define X(name, callback, parent, object) \
		create_menu_item_with_callback(name, parent, callback, object);
	MENU_SETUP
	#undef X

	gtk_menu_item_set_submenu(GTK_MENU_ITEM (menuItem), subMenu);

    	gtk_box_pack_start(GTK_BOX (box), menuBar, FALSE, FALSE, 5);
    	gtk_box_pack_start(GTK_BOX (box), area, TRUE, TRUE, 5);

	g_signal_connect (G_OBJECT (area), "draw", G_CALLBACK (draw_callback), NULL);
	gtk_widget_add_tick_callback(area, trigger_draw, NULL, stub_destroy);

	//TODO: set the callback to setup_callback. The callback will then
	//subscribe itself to display proxy to receive the correct signal.


	gtk_container_add(GTK_CONTAINER (window), box);
	gtk_widget_show_all (window);
}

