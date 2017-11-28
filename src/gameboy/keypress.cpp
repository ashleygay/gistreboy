#include <keypress.hpp>

void display_key_press(KeyPress p)
{

	switch (p) {
		case KeyPress::DOWN :
			DEBUG_STREAM << "Key pressed : " << "DOWN"
				     << std::endl;
			break;
		case KeyPress::UP :
			DEBUG_STREAM << "Key pressed : " << "UP"
				     << std::endl;
			break;
		case KeyPress::RIGHT :
			DEBUG_STREAM << "Key pressed : " << "RIGHT"
				     << std::endl;
			break;
		case KeyPress::LEFT :
			DEBUG_STREAM << "Key pressed : " << "LEFT"
				     << std::endl;
			break;
		case KeyPress::A :
			DEBUG_STREAM << "Key pressed : " << "A"
				     << std::endl;
			break;
		case KeyPress::B :
			DEBUG_STREAM << "Key pressed : " << "B"
				     << std::endl;
			break;
		case KeyPress::START :
			DEBUG_STREAM << "Key pressed : " << "START"
				     << std::endl;
			break;
		case KeyPress::SELECT :
			DEBUG_STREAM << "Key pressed : " << "SELECT"
				     << std::endl;
			break;
	}
}
