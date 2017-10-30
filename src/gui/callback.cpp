/*
 * File : callback.cpp
 *
 * File created by : Corentin Gay
 * File was created the : 08/09/2017
 */

#include <callback.hpp>

void NYI(GtkWidget * b, gpointer user_data)
{
	(void)user_data;
	DEBUG_STREAM << "Button \"" << gtk_menu_item_get_label(GTK_MENU_ITEM(b))
		    << "\" not yet implemented." << std::endl;
}

void stop_callback(GtkWidget * w, gpointer user_data)
{
	(void)w;
	(void)user_data;
	DEBUG_STREAM << "Stopping the emulation." << std::endl;
	EmuInterface::getInstance().stopEmulator();
}


void open_button_callback(GtkWidget * b, gpointer user_data)
{
	(void)b;
	OpenButtonHelper *helper = (OpenButtonHelper *)user_data;
	GFile* g = helper->open_file_with_dialog();
	FileContent data = helper->load_content(g);

	if (!data.memory)
		return;

	EmuInterface & i = EmuInterface::getInstance();

	// EmuInterface takes ownership of the data pointer
	i.changeCartridge(data);

	DEBUG_STREAM << "We give the pointer to the memory here." << std::endl;
}

void run_button_callback(GtkWidget * b, gpointer user_data)
{
	(void)b;
	(void)user_data;

	EmuInterface& i = EmuInterface::getInstance();

	i.startEmulator();
}

gboolean draw_callback(GtkWidget * w, cairo_t *cr, gpointer user_data)
{
//	using namespace std::chrono_literals;
	(void)user_data;

//	DEBUG_STREAM << "Draw area callback" << std::endl;
//	DEBUG_STREAM << "Cairo object pointer is : " << (void*)cr<< std::endl;

	//TODO: get an instance of emu_interface and get the buffer to render

	int width = 0, height = 0;
	GtkStyleContext *context;

	context = gtk_widget_get_style_context(w);
	width = gtk_widget_get_allocated_width(w);
	height = gtk_widget_get_allocated_height(w);

//	std::this_thread::sleep_for(2s);
//	DEBUG_STREAM << "Dimensions : " << width  << " x " << height << std::endl;

	gtk_render_background(context, cr, 0, 0, width, height);

  	cairo_arc (cr,
             width / 2.0, height / 2.0,
             MIN (width, height) / 2.0,
             0, 2 * G_PI);

	GdkRGBA black = {0.0, 0.0, 0.0, 1.0};

	gdk_cairo_set_source_rgba(cr, &black);
	cairo_fill(cr);

	return FALSE;
}

int trigger_draw(GtkWidget * area, GdkFrameClock * c, gpointer user_data)
{
	(void)c;
	(void)user_data;
//	DEBUG_STREAM << "Triggering draw event on the area. clock " << (void*)c << std::endl;
	gtk_widget_queue_draw_area(area, 0, 0,
			gtk_widget_get_allocated_width(area),
			gtk_widget_get_allocated_height(area));
	return 42;
}
