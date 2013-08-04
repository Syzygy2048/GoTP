#include "InputHandlerSFML.h"

InputHandlerSFML::InputHandlerSFML(void)
{
}

void InputHandlerSFML::poll()
{
	oldBitmask = clickBitmask;
	clickBitmask = 0;
	mousePos = sf::Mouse::getPosition();
	if(sf::Mouse::isButtonPressed(sf::Mouse::Left))	clickBitmask ^= mouseButtonLeft; 
	if(sf::Mouse::isButtonPressed(sf::Mouse::Right)) clickBitmask ^= mouseButtonRight; 

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) clickBitmask ^= keySPACE;
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)) clickBitmask ^= keyW;
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)) clickBitmask ^= keyA;
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)) clickBitmask ^= keyS;	
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)) clickBitmask ^= keyD;

	holdBitmask = oldBitmask & clickBitmask;	
}

InputHandlerSFML* InputHandlerSFML::getInstance()
{
	static InputHandlerSFML* instance;
	return instance;
}

InputHandlerSFML::~InputHandlerSFML(void)
{
}
