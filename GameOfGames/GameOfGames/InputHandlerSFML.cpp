#include "InputHandlerSFML.h"
#include "SceneGraph\SceneNode.h"
#include "SceneGraph\UIView.h"
#include "FocusGroup.h"

InputHandlerSFML::InputHandlerSFML(void)
{

}

void InputHandlerSFML::setFocusGroupSet(std::vector<FocusGroup*>* set)
{
	focusGroupSet = set;

	if(focusGroupSet)
	{
		setActiveFocusGroup(focusGroupSet->at(0));
	}
	else
	{
		if(activeFocusGroup)
		{
			activeFocusGroup->setActive(false);

			activeFocusGroup = NULL;
		}
	}
}

void InputHandlerSFML::informMouseClicked(int key)
{
	mouseClicked = true;
	mouseClickedKey = key;
}

void InputHandlerSFML::setActiveFocusGroup(unsigned int index)
{
	if(focusGroupSet && index < focusGroupSet->size())
	{
		setActiveFocusGroup(focusGroupSet->at(activeFocusGroupIndex));
	}
	else
	{
		std::cout<<"Couldnt set an active focus group by index because there isnt a focus group set.";
	}
}

void  InputHandlerSFML::informDpadChanged(DpadDirection direction)
{
	if(activeFocusGroup)
	{
		if((direction == UP || direction == DOWN)&& activeFocusGroup->getOrientation() == HORIZONTAL || 
			(direction == LEFT || direction == RIGHT)&& activeFocusGroup->getOrientation() == VERTICAL )
		{
			if(focusGroupSet)
			{
				if(direction == UP || direction == LEFT)
				{
					if(activeFocusGroupIndex > 0)
					{
						setActiveFocusGroup(activeFocusGroupIndex--);
					}
				}
				else if(activeFocusGroupIndex < focusGroupSet->size()-1)
				{
					setActiveFocusGroup(activeFocusGroupIndex++);
				}
			}
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

	if(activeFocusGroup)
	{
		activeFocusGroup->setActive(true);

		if(focusGroupSet)
		{
			for (unsigned int i = 0; i <focusGroupSet->size();i++)
			{
				if(focusGroupSet->at(i)== activeFocusGroup)
				{
					activeFocusGroupIndex = i;
					break;
				}
			}
		}
	}
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
