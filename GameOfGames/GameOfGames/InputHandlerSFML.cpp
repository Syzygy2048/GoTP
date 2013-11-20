#include "InputHandlerSFML.h"
#include "SceneGraph\SceneNode.h"
#include "SceneGraph\UIView.h"

InputHandlerSFML::InputHandlerSFML(void)
{
	clickBitmask = 0;
	oldBitmask = 0;
	holdBitmask = 0;
}

void InputHandlerSFML::clearClickable()
{
	drawnClickable = NULL;
}

void InputHandlerSFML::setDrawnClickable(UIView* clicked)
{
	drawnClickable = clicked;
}

void InputHandlerSFML::checkOnClickable()
{
	if (drawnClickable && drawnClickable->getFocusable())
	{
		if(!drawnClickable->getHoveredState() && drawnClickable->isHoverable())
		{
			if (lastHovered)
			{
				lastHovered->setHoveredState(false);
			}

			lastHovered = drawnClickable;

			lastHovered->setHoveredState(true);
		}
		else if(drawnClickable->getHoveredState() && !drawnClickable->isHoverable())
		{
			drawnClickable->setHoveredState(false);

			lastHovered = NULL;
		}
		else if(lastHovered && lastHovered!= drawnClickable)
		{
			lastHovered->setHoveredState(false);

			lastHovered = NULL;
		}

		if(InputHandlerSFML::getInstance()->didClicked())
		{
			drawnClickable->activated();
		}
	}
	else if(lastHovered)
	{
		lastHovered->setHoveredState(false);

		lastHovered = NULL;
	}
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
