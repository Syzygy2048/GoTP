#pragma once
#include <vector>
#include <iostream>
#include "Enums.h"

class UIView;

class UIViewListener
{
public:
	virtual void viewHovered(UIView* sender, bool hoveredState){}
	virtual void viewSelected(UIView* sender, ConfirmSource source, int key){}
	virtual void viewFocused(UIView* sender, bool focusedState){}
};
