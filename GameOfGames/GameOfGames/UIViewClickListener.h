#pragma once
#include <vector>
#include <iostream>

class UIView;

class UIViewClickListener
{
public:
	static void addDrawnClickable(UIView* clickable,bool clear);

	virtual void viewClicked(UIView* sender){};

};
