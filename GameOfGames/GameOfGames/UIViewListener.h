#pragma once
#include <vector>
#include <iostream>

class UIView;

class UIViewListener
{
public:
	virtual void viewHovered(UIView* sender, bool hoveredState){}
	virtual void viewClicked(UIView* sender, int key){}
	virtual void viewFocused(UIView* sender, bool focusedState){}
};
