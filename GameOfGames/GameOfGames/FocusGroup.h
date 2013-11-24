#pragma once
#include <vector>

class UIView;

enum GroupOrientation {VERTICAL, HORIZONTAL};

class FocusGroup
{
public:
	FocusGroup();
	~FocusGroup();

	void insertFocusable(UIView* newFocusable);

	//May be bugged, didnt tested yet.
	void removeFocusable(UIView* toRemove);

	void changeFocusable(bool positiveAxis);
	void forceFocusable(int index);
	
	GroupOrientation getOrientation(){return orientation;}
	void setOrientation(GroupOrientation newOrientation){orientation = newOrientation;}
	
	void setActive(bool newisActive);
	bool getActive(){return isActive;}

	bool getIsLooped(){return isLooped;}
	void setLooped(bool newIsLooped){isLooped = newIsLooped;}

private:
	bool isActive;
	bool isLooped;
	unsigned int focusedIndex;
	UIView* currentFocused;
	GroupOrientation orientation;
	std::vector<UIView*>* focusables;
};