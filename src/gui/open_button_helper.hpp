#pragma once

#include <gtk/gtk.h>
#include <debug.hpp>
#include <iostream>
#include <fstream>
#include <string.h>
#include <unordered_map>

using str_to_str = std::unordered_map<std::string, std::string>;

class Helper
{
	public:
		void set_window(GtkWidget * window) {_window = window;}
		GtkWidget * get_window(void) {return _window;}

		template<typename T, typename... Args>
		void message_dialog_display(T t, Args... args)
		{
			if (!_window) {
				DEBUG_PRINT << "Trying to call message_dialog_display without a parent window."
				<< " Call set_window before calling that function" << std::endl;
				return;
			}
			GtkWidget * dialog = gtk_message_dialog_new(GTK_WINDOW(_window),
			GTK_DIALOG_MODAL, GTK_MESSAGE_ERROR, GTK_BUTTONS_OK, t, args...);

			gtk_dialog_run(GTK_DIALOG (dialog));
			gtk_widget_destroy(dialog);
		}

	private:
		GtkWidget * _window = NULL;
};

class OpenButtonHelper : public Helper
{
	public:
		OpenButtonHelper(size_t min_size, str_to_str attributes):
				Helper(), _min_size(min_size),
				_attributes(attributes){}

	public:
		int verify_checksum(const char * data);

		GFile* open_correct_file(void);

		//TODO: load content of file into a memory zone
		char * load_content(GFile* f);

	private:
		int verify_min_size(GFile * f);
		int verify_attributes(GFile * f);

	private:
		size_t _min_size;
		str_to_str _attributes;
};
