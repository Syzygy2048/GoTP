#pragma once
#include <vector>
#include <iostream>

class UIView;

class UIViewClickListener
{
public:
	virtual void viewClicked(UIView* sender){};
};
