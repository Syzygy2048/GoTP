#pragma once

#include <SFML\Window.hpp>
#include <SFML\Graphics.hpp>
#include "Enums.h"

class UIView;
class FocusGroup;

class InputHandlerSFML
{
public:
	static InputHandlerSFML* getInstance();

	//Clear all events that happened on the last frame. Dont call.
	void clearOcurredEvents();

	void informMouseClicked(int button);
	void informMouseMoved(sf::Vector2i location);

	//Puts the view as the view under the mouse.
	void setMouseInteractive(UIView* clicked);

	//Checks for the view under the mouse.
	void checkOnMouseInteractive();
	void informConfirmPressed(ConfirmSource source, int key);

	void setActiveFocusGroup(FocusGroup* group);
	void setActiveFocusGroup(unsigned int index);

	void setFocusGroupSet(std::vector<FocusGroup*>* set);

	void informDpadChanged(DpadDirection direction);

	sf::Vector2i* getMousePosition() {return &mousePos; }

	bool didClicked(){ return mouseClicked; }

private:
	InputHandlerSFML(void);										
	InputHandlerSFML(const InputHandlerSFML&);	
	InputHandlerSFML& operator = (const InputHandlerSFML&);

	InputHandlerSFML* instance;
	FocusGroup* activeFocusGroup;
	UIView* lastMouseInteractive;
	UIView* mouseInteractive;

	std::vector<FocusGroup*>* focusGroupSet;
	sf::Vector2i mousePos;

	unsigned int activeFocusGroupIndex;
	int mouseClickedKey;
	bool mouseClicked;
};

