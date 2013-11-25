#include "InputHandlerSFML.h"
#include "SceneGraph\SceneNode.h"
#include "SceneGraph\UIView.h"
#include "FocusGroup.h"

InputHandlerSFML::InputHandlerSFML(void)
{

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

void InputHandlerSFML::clearOcurredEvents()
{
	mouseClicked = false;
	mouseClickedKey = -1;
}

void InputHandlerSFML::informMouseClicked(int key)
{
	mouseClicked = true;
	mouseClickedKey = key;
}

void InputHandlerSFML::informMouseMoved(sf::Vector2i location)
{
	mousePos = location;
}

void InputHandlerSFML::setMouseInteractive(UIView* clicked)
{
	mouseInteractive = clicked;
}

void InputHandlerSFML::checkOnMouseInteractive()
{
	if (mouseInteractive && mouseInteractive->getFocusable())
	{
		if(!mouseInteractive->getHoveredState() && mouseInteractive->isHoverable())
		{
			if (lastMouseInteractive)
			{
				lastMouseInteractive->setHoveredState(false);
			}

			lastMouseInteractive = mouseInteractive;

			lastMouseInteractive->setHoveredState(true);
		}
		else if(mouseInteractive->getHoveredState() && !mouseInteractive->isHoverable())
		{
			mouseInteractive->setHoveredState(false);

			lastMouseInteractive = NULL;
		}
		else if(lastMouseInteractive && lastMouseInteractive!= mouseInteractive)
		{
			lastMouseInteractive->setHoveredState(false);

			lastMouseInteractive = NULL;
		}

		if(mouseClicked)
		{
			mouseInteractive->activated(ConfirmSource::MOUSE,mouseClickedKey);
		}
	}
	else if(lastMouseInteractive)
	{
		lastMouseInteractive->setHoveredState(false);

		lastMouseInteractive = NULL;
	}
}

void InputHandlerSFML::informConfirmPressed(ConfirmSource source, int key)
{
	if(activeFocusGroup)
	{
		activeFocusGroup->focusableSelected(source, key);
	}
}

void InputHandlerSFML::setActiveFocusGroup(unsigned int index)
{
	if(focusGroupSet && index < focusGroupSet->size())
	{
		setActiveFocusGroup(focusGroupSet->at(activeFocusGroupIndex));
	}
	else
	{
		std::cout<<"Couldnt set an active focus group by index because there isnt a focus group set or because the index is out of bounds of the set.\n";
	}
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
			activeFocusGroup->iterateFocusables(direction == DOWN);
		}
		else
		{
			activeFocusGroup->iterateFocusables(direction == LEFT);
		}
	}
}




