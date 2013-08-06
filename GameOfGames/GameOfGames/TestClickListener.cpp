#include "TestClickListener.h"

void TestClickListener::viewHovered(UIView* sender, bool hoveredState)
{
	if (hoveredState)
	{
		sender->setTintColor(255,128,128);
	}
	else
	{
		sender->resetTintColor();
	}
}

void TestClickListener::viewClicked(UIView* sender)
{
	std::cout<<"view at "<<sender->getCachedLocation()->x<<", "<<sender->getCachedLocation()->y<<" got clicked.\n"; 
}