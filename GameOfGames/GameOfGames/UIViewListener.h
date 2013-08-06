#pragma once
#include <vector>
#include <iostream>
#include "SceneGraph\UIView.h"

class UIView;

class UIViewListener
{
public:
	virtual void viewHovered(UIView* sender, bool hoveredState){};
	virtual void viewClicked(UIView* sender){};
};
