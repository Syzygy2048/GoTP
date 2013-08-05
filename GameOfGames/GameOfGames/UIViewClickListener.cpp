#include "UIViewClickListener.h"

void UIViewClickListener::addDrawnClickable(UIView* clickable,bool clear)
{
	static std::vector<UIView*> drawnClickables;

	if (clear)
	{
		while (!drawnClickables.empty())
		{
			drawnClickables.pop_back();
		}
	}
	else
	{
		drawnClickables.push_back(clickable);
	}
}

