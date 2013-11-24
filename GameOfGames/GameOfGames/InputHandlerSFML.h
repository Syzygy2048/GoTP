#pragma once

#include <SFML\Window.hpp>
#include <SFML\Graphics.hpp>

enum DpadDirection{LEFT, RIGHT, UP, DOWN};

class UIView;
class FocusGroup;

class InputHandlerSFML
{
public:
	static InputHandlerSFML* getInstance();

	void clearOcurredEvents();
	void informMouseClicked(int button);
	void informMouseMoved(sf::Vector2i location);
	void clearClickable();
	void setDrawnClickable(UIView* clicked);
	void checkOnClickable();

	void setActiveFocusGroup(FocusGroup* group);
	void setActiveFocusGroup(unsigned int index);

	void setFocusGroupSet(std::vector<FocusGroup*>* set);

	void informDpadChanged(DpadDirection direction);

	sf::Vector2i* getMousePosition() {return &mousePos; }

	bool didClicked(){ return mouseClicked; }

	~InputHandlerSFML(void);

private:
	unsigned int activeFocusGroupIndex;
	FocusGroup* activeFocusGroup;
	std::vector<FocusGroup*>* focusGroupSet;
	bool mouseClicked;
	int mouseClickedKey;
	bool mouseMoved;
	InputHandlerSFML* instance;
	InputHandlerSFML(void);										//private because singleton
	InputHandlerSFML(const InputHandlerSFML&);					//prevents copy constructor
	InputHandlerSFML& operator = (const InputHandlerSFML&);		//prevents copy

	sf::Vector2i mousePos;

	UIView* lastHovered;
	UIView* drawnClickable;

};

