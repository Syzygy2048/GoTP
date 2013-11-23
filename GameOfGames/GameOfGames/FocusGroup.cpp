#include "FocusGroup.h"
#include "SceneGraph\UIView.h"

FocusGroup::FocusGroup()
{
	isLooped = true;
	orientation = HORIZONTAL;
	isActive = false;
}

void FocusGroup::changeFocusable(bool positiveAxis)
{
	if(focusables->size()==0)
	{
		return;
	}

	if(currentFocused)
	{
		currentFocused->setFocusedState(false);
	}

	if (positiveAxis)
	{
		if (focusedIndex < focusables->size()-1)
		{
			focusedIndex++;
		}
		else if(isLooped)
		{
			focusedIndex = 0;
		}
	}
	else
	{
		if (focusedIndex>0)
		{
			focusedIndex--;
		}
		else if(isLooped)
		{
			focusedIndex = focusables->size()-1;
		}
	}

	currentFocused = focusables->at(focusedIndex);

	currentFocused->setFocusedState(true);
}

void FocusGroup::insertFocusable(UIView* newFocusable)
{
	newFocusable->setFocusGroup(this);

	if (!focusables)
	{
		focusedIndex = 0;
		focusables = new std::vector<UIView*>();
		currentFocused = newFocusable;

		if(isActive)
		{
			currentFocused->setFocusedState(true);
		}
	}

	focusables->push_back(newFocusable);
}

void FocusGroup::removeFocusable(UIView* toRemove)
{
	if(focusables)
	{
		focusables->erase(std::remove(focusables->begin(), focusables->end(), toRemove), focusables->end());

		if(focusedIndex == focusables->size())
		{
			focusedIndex--;
		}
	}
}

void FocusGroup::setActive(bool newisActive)
{
	if(currentFocused)
	{
		currentFocused->setFocusedState(newisActive);
	}

	isActive = newisActive;
}

FocusGroup::~FocusGroup(void)
{
	if(focusables)
	{
		for each (UIView* focusable in *focusables)
		{
			focusable->setFocusGroup(NULL);
		}

		delete focusables;
	}
}