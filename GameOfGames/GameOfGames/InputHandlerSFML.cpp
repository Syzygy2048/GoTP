#include "InputHandlerSFML.h"
#include "SceneGraph\SceneNode.h"
#include "SceneGraph\UIView.h"
#include "FocusGroup.h"

InputHandlerSFML::InputHandlerSFML(void)
{

}

void InputHandlerSFML::informMouseClicked(int key)
{
	mouseClicked = true;
	mouseClickedKey = key;
}

void  InputHandlerSFML::informDpadChanged(DpadDirection direction)
{
	if(activeFocusGroup)
	{
		if((direction == UP || direction == DOWN)&& activeFocusGroup->getOrientation() == HORIZONTAL || 
			(direction == LEFT || direction == RIGHT)&& activeFocusGroup->getOrientation() == VERTICAL )
		{
			return;
		}

		if(activeFocusGroup->getOrientation()==VERTICAL)
		{
			activeFocusGroup->changeFocusable(direction == DOWN);
		}
		else
		{
			activeFocusGroup->changeFocusable(direction == LEFT);
		}
	}
}

void InputHandlerSFML::informMouseMoved(sf::Vector2i location)
{
	mouseMoved = true;

	mousePos = location;

}

void InputHandlerSFML::clearOcurredEvents()
{
	mouseClicked = false;
	mouseClickedKey = -1;
	mouseMoved = false;
}

void InputHandlerSFML::clearClickable()
{
	drawnClickable = NULL;
}

void InputHandlerSFML::setDrawnClickable(UIView* clicked)
{
	drawnClickable = clicked;
}

void InputHandlerSFML::setActiveFocusGroup(FocusGroup* group)
{
	if (activeFocusGroup)
	{
		activeFocusGroup->setActive(false);
	}

	activeFocusGroup = group;

	activeFocusGroup->setActive(true);


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

		if(mouseClicked)
		{
			drawnClickable->activated(mouseClickedKey);
		}
	}
	else if(lastHovered)
	{
		lastHovered->setHoveredState(false);

		lastHovered = NULL;
	}
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
