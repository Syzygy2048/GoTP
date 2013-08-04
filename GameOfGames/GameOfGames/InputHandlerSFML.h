#pragma once

#include <SFML\Window.hpp>
#include "SceneGraph\SceneNode.h"
#include <cstdint>

#define keyW (uint64_t) pow(2,0)
#define keyA (uint64_t) pow(2,1)
#define keyS (uint64_t) pow(2,2)
#define keyD (uint64_t) pow(2,3)
#define keySPACE (uint64_t) pow(2,4)
#define mouseButtonLeft (uint64_t) pow(2,5)
#define mouseButtonRight (uint64_t) pow(2,6)


class InputHandlerSFML
{
public:


	static InputHandlerSFML& getInstance();
	
	//checks the keyboard for all currently pressed keys and loads them into bitmasks, only call once per frame from within the game loop.
	void poll();

	//returns a bitmask of all defined keys currently pressed down
	uint64_t getKeysPressed(){ return clickBitmask; }
	//returns a bitmask of all defined keys that are held down for more than a frame already
	uint64_t getKeysHeld(){ return holdBitmask; }
	
	sf::Vector2i* getMousePosition() {return &mousePos; }


	//void subscribeToEvent(void (*callbackFunction)(IHandleInput*), uint64_t subMask);

	~InputHandlerSFML(void);

private:
	InputHandlerSFML* instance;
	InputHandlerSFML(void);										//private because singleton
	InputHandlerSFML(const InputHandlerSFML&);					//prevents copy constructor
	InputHandlerSFML& operator = (const InputHandlerSFML&);		//prevents copy

	sf::Vector2i mousePos;

	uint64_t clickBitmask;
	uint64_t holdBitmask;
	uint64_t oldBitmask;
};

