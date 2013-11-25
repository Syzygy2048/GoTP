#pragma once
#include <vector>
#include "Enums.h"

class UIView;

class FocusGroup
{
public:
	FocusGroup();
	~FocusGroup();

	void insertFocusable(UIView* newFocusable);

	//May be bugged, didnt tested yet.
	void removeFocusable(UIView* toRemove);

	void focusableSelected(ConfirmSource source, int key);

	//If true, will go to next, else will go to previous.
	void iterateFocusables(bool positiveAxis);

	//Skips to a focusable in the group.
	void selectFocusable(unsigned int index);
	void selectFocusable(UIView* focusable);

	GroupOrientation getOrientation(){return orientation;}
	void setOrientation(GroupOrientation newOrientation){orientation = newOrientation;}

	void setActive(bool newisActive);
	bool getActive(){return isActive;}

	bool getIsLooped(){return isLooped;}
	void setLooped(bool newIsLooped){isLooped = newIsLooped;}

private:
	UIView* currentFocused;
	std::vector<UIView*>* focusables;

	GroupOrientation orientation;
	bool isActive;
	bool isLooped;
	unsigned int focusedIndex;

};