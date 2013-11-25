#pragma once
#include "UIViewListener.h"

class TestClickListener : public UIViewListener
{
public:
	 void viewHovered(UIView* sender, bool hoveredState);
	 void viewSelected(UIView* sender, ConfirmSource source, int key);
	 void viewFocused(UIView* sender, bool focusedState);
};