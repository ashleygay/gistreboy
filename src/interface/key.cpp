#include <key.hpp>

void display_key(Key k)
{
	switch (k) {
		case Key::DOWN :
			std::cout << "Key : " << "DOWN"
				     << std::endl;
			break;
		case Key::UP :
			std::cout << "Key : " << "UP"
				     << std::endl;
			break;
		case Key::RIGHT :
			std::cout << "Key : " << "RIGHT"
				     << std::endl;
			break;
		case Key::LEFT :
			std::cout << "Key : " << "LEFT"
				     << std::endl;
			break;
		case Key::A :
			std::cout << "Key : " << "A"
				     << std::endl;
			break;
		case Key::B :
			std::cout << "Key : " << "B"
				     << std::endl;
			break;
		case Key::START :
			std::cout << "Key : " << "START"
				     << std::endl;
			break;
		case Key::SELECT :
			std::cout << "Key : " << "SELECT"
				     << std::endl;
			break;
	}
}
