#include <key.hpp>

void display_key(Key k)
{
	switch (k) {
		case Key::DOWN :
			DEBUG_STREAM << "Key : " << "DOWN"
				     << std::endl;
			break;
		case Key::UP :
			DEBUG_STREAM << "Key : " << "UP"
				     << std::endl;
			break;
		case Key::RIGHT :
			DEBUG_STREAM << "Key : " << "RIGHT"
				     << std::endl;
			break;
		case Key::LEFT :
			DEBUG_STREAM << "Key : " << "LEFT"
				     << std::endl;
			break;
		case Key::A :
			DEBUG_STREAM << "Key : " << "A"
				     << std::endl;
			break;
		case Key::B :
			DEBUG_STREAM << "Key : " << "B"
				     << std::endl;
			break;
		case Key::START :
			DEBUG_STREAM << "Key : " << "START"
				     << std::endl;
			break;
		case Key::SELECT :
			DEBUG_STREAM << "Key : " << "SELECT"
				     << std::endl;
			break;
	}
}
