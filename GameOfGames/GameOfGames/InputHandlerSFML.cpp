#include "InputHandlerSFML.h"

InputHandlerSFML::InputHandlerSFML(void)
{
	clickBitmask = 0;
	oldBitmask = 0;
	holdBitmask = 0;
}

void InputHandlerSFML::poll(sf::RenderWindow* window)
{
	oldBitmask = clickBitmask;
	clickBitmask = 0;
	mousePos = sf::Mouse::getPosition(*window);
	if(sf::Mouse::isButtonPressed(sf::Mouse::Left))	clickBitmask ^= mouseButtonLeft; 
	if(sf::Mouse::isButtonPressed(sf::Mouse::Right)) clickBitmask ^= mouseButtonRight; 

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) clickBitmask ^= keySPACE;
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)) clickBitmask ^= keyW;
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)) clickBitmask ^= keyA;
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)) clickBitmask ^= keyS;	
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)) clickBitmask ^= keyD;

	holdBitmask = oldBitmask & clickBitmask;	

	clicked = !(mouseButtonLeft == (mouseButtonLeft & getKeysHeld())) && ((mouseButtonLeft == (mouseButtonLeft & getKeysPressed())));
}

InputHandlerSFML* InputHandlerSFML::getInstance()
{
	static InputHandlerSFML* instance;
	
	if(!instance)
	{
		instance = new InputHandlerSFML();
	}
	
	return instance;
}

InputHandlerSFML::~InputHandlerSFML(void)
{
}
