#include "InputHandlerSFML.h"


InputHandlerSFML::InputHandlerSFML(void)
{
}

void InputHandlerSFML::poll()
{
	mousePos = sf::Mouse::getPosition();
	if(sf::Mouse::isButtonPressed(sf::Mouse::Left))	bitmask ^= mouseButtonLeft; 
	if(sf::Mouse::isButtonPressed(sf::Mouse::Right)) bitmask ^= mouseButtonRight; 

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) bitmask ^= space;
	
}

InputHandlerSFML* InputHandlerSFML::getInstance()
{
	static InputHandlerSFML* instance;
	return instance;
}

InputHandlerSFML::~InputHandlerSFML(void)
{
}
