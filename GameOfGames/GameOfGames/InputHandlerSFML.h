#pragma once

#include <SFML\Window.hpp>
#include <SFML\Graphics.hpp>

#define keyW (uint64_t) pow(2,0)
#define keyA (uint64_t) pow(2,1)
#define keyS (uint64_t) pow(2,2)
#define keyD (uint64_t) pow(2,3)
#define keySPACE (uint64_t) pow(2,4)
#define mouseButtonLeft (uint64_t) pow(2,5)
#define mouseButtonRight (uint64_t) pow(2,6)

class UIView;

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

	sf::Vector2i* getMousePosition() {return &mousePos; }

	bool didClicked(){ return mouseClicked; }

	~InputHandlerSFML(void);

private:
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

