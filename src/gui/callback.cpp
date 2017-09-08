#include "callback.hpp"

void NYI(GtkWidget * b, gpointer user_data)
{
	DEBUG_PRINT << "Button \"" << gtk_menu_item_get_label(GTK_MENU_ITEM(b))
		    << "\" not yet implemented." << std::endl;
}

void quit_callback(GtkWidget * w, gpointer data)
{
	DEBUG_PRINT << "Quitting the application." << std::endl;
	GtkWidget *window = (GtkWidget *)data;
	gtk_widget_destroy(window);
}


void open_button_callback(GtkWidget * b, gpointer user_data)
{
	OpenButtonHelper *helper = (OpenButtonHelper *)user_data;
	GFile* gf = helper->open_correct_file();
	char * data = helper->load_content(gf);
	if (!data)
		return;
	//TODO: we give the pointer to the memory here.
	DEBUG_PRINT << "TODO: we give the pointer to the memory here." << std::endl;

	free(data);
}

gboolean draw_callback(GtkWidget * w, cairo_t *cr, gpointer user_data)
{
	(void)user_data;

	DEBUG_PRINT << "Draw area callback" << std::endl;
	DEBUG_PRINT << "Cairo object pointer is : " << (void*)cr<< std::endl;

	//TODO: update the function to actually take into account that the
	//buffer has changed

	int width = 0, height = 0;
	GdkRGBA color;
	GtkStyleContext *context;
	cairo_surface_t *cs;

	context = gtk_widget_get_style_context(w);
	width = gtk_widget_get_allocated_width(w);
	height = gtk_widget_get_allocated_height(w);

	DEBUG_PRINT << "Dimensions : " << width  << " x " << height << std::endl;

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
	DEBUG_PRINT << "Triggering draw event on the area. clock " << (void*)c << std::endl;
	gtk_widget_queue_draw_area(area, 0, 0,
			gtk_widget_get_allocated_width(area),
			gtk_widget_get_allocated_height(area));
	return 42;
}
