#include "display_proxy.hpp"


void DisplayProxy::access_buffer(void)
{
	if (_to_update) {
		DEBUG_PRINT << "Will get buffer to display from emulator" << std::endl;
	}
}

void DisplayProxy::register_observer(GtkWidget *w, cairo_t * cr)
{
	DEBUG_PRINT << "Registering widget" << (void*)w
		<< " and cairo object" << (void*)cr<< std::endl; 
	_observers[w] = cr;
}

void DisplayProxy::notifyObservers(const char * buffer)
{
	for (const auto& p : _observers) {
		DEBUG_PRINT << "Emitting signal with widget" << (void*)p.first
		<< " and cairo object" << (void*)p.second<< std::endl;
		//TODO: g_signal_emit(tab, id, G_QUARK("draw"), NULL);
		//TODO: lookup va_copy and friends
	}
}

void DisplayProxy::updateBuffer(void)
{
	//TODO: update the buffer or do something with it.
	DEBUG_PRINT << "Will update the observers." << std::endl;
	//TODO: g_signal_emit on all the obervers.
	_to_update = 1;

}
