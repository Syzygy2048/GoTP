#pragma once
#include "UIViewListener.h"

class TestClickListener : public UIViewListener
{
public:
	 void viewHovered(UIView* sender, bool hoveredState);
	 void viewClicked(UIView* sender, int key);
	 void viewFocused(UIView* sender, bool focusedState);
};