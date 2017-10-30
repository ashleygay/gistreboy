/*
 * File : open_button_helper.cpp
 *
 * File created by : Corentin Gay
 * File was created the : 08/09/2017
 */

#include <open_button_helper.hpp>

FileContent OpenButtonHelper::load_content(GFile* gf)
{
	std::ifstream file(g_file_get_path(gf), std::ios::in | std::ios::binary);

	if (!file.is_open())
		return {NULL, 0};

	size_t size = 0;

	file.seekg(0, std::ios::end);
    	size = file.tellg();
	// We reset the position of the cursor to the beginning of the file
	file.seekg(0, std::ios::beg);

	DEBUG_STREAM << "Copying file into buffer size : " << size << std::endl;
	DEBUG_STREAM << "Buffer is :" << std::endl;
	// We get the content of the file
	uint8_t * mem = (uint8_t *)malloc(size);
	if (mem) {
		for (uint i = 0; i < size; ++i) {
			mem[i] = file.get(); 
			DEBUG_STREAM << (char)mem[i];
		}
	}

	return {mem, size};
}

bool OpenButtonHelper::verify_attributes(GFile * f)
{
	DEBUG_STREAM << "Checking attributes of "
		     << g_file_get_path(f) << std::endl; 

	// We check that all attributes for the given files are respected
	for (auto pair : _attributes) {
		const char * attribute = pair.first.c_str();
		const char * value = pair.second.c_str();

		// We query infos from the file.
		GFileInfo *info = g_file_query_info(f,
						attribute,
						G_FILE_QUERY_INFO_NONE,
						NULL,
						NULL);

		DEBUG_STREAM << "Checking attribute "
			     << attribute
			     << "\n\twanted value is "
			     << value << std::endl; 

		const char * actual_val;
		actual_val = g_file_info_get_attribute_as_string(info,
								 attribute);
		DEBUG_STREAM << "\tactual value is " << actual_val << std::endl; 

		if (strcmp(actual_val, value))
			return false;
	}
	DEBUG_STREAM << "Succesfully checked all attributes." << std::endl;
	return true;
}

bool OpenButtonHelper::verify_min_size(GFile * f)
{
	GFileInfo *info = g_file_query_info(f,
					    "standard::size",
					    G_FILE_QUERY_INFO_NONE,
					    NULL,
					    NULL);
	if (!info)
		return 0;

	size_t size = g_file_info_get_size(info);
	DEBUG_STREAM << "Min size is " << _min_size << " file size is " << size << std::endl;
	return size >= _min_size;
}

GFile* OpenButtonHelper::open_file_with_dialog(void)
{
	GtkWidget *dialog;	
	GtkFileChooserAction action = GTK_FILE_CHOOSER_ACTION_OPEN;	
	GFile *g = NULL;
	int file_ok = 0, res = 0;

	GtkWidget * w = _window;
	if (!w) {
		DEBUG_STREAM << "Trying to call open_correct_file without a parent window."
				<< " Call set_window before calling that function" << std::endl;
		return NULL;

	}
	dialog = gtk_file_chooser_dialog_new("Open File",
					     GTK_WINDOW(w),
					     action,
					     ("_Cancel"),
					     GTK_RESPONSE_CANCEL,
					     ("_Open"),
					     GTK_RESPONSE_ACCEPT,
					     NULL);


	while (!file_ok) {
		res = gtk_dialog_run(GTK_DIALOG (dialog));
		if (res == GTK_RESPONSE_ACCEPT) {
			GtkFileChooser *chooser = GTK_FILE_CHOOSER (dialog);
			char * filename = gtk_file_chooser_get_filename (chooser);
			DEBUG_STREAM << "Opening : " << filename << std::endl;
			g = g_file_new_for_path(filename);
			file_ok = verify_attributes(g) && verify_min_size(g);
			if (!file_ok) message_dialog_display("Could not open file %s", filename);
			g_free(filename);
		}
		else
			break;
	}
	gtk_widget_destroy (dialog);
	return g;
}
