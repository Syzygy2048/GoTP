#pragma once
#include <SFML\Window.hpp>
#include "IHandleInput.h"
#include <cstdint>

#define w (uint64_t) pow(2,0)
#define a (uint64_t) pow(2,1)
#define s (uint64_t) pow(2,2)
#define d (uint64_t) pow(2,3)
#define space (uint64_t) pow(2,4)
#define mouseButtonLeft (uint64_t) pow(2,5)
#define mouseButtonRight (uint64_t) pow(2,6)


class InputHandlerSFML
{
public:

	~InputHandlerSFML(void);

	static InputHandlerSFML* getInstance();
	void poll();

	//void subscribeToEvent(void (*callbackFunction)(IHandleInput*), uint64_t subMask);


private:
	InputHandlerSFML(void);										//private because singleton
	InputHandlerSFML(const InputHandlerSFML&);					//prevents copy constructor
	InputHandlerSFML& operator = (const InputHandlerSFML&);		//prevents copy

	sf::Vector2i mousePos;


	uint64_t bitmask;

};

