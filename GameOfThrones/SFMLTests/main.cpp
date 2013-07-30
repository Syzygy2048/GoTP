#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "SceneNode.h"
#include "TestChar.h"

#define TIMESTEP 0.01666666666f

std::vector<SceneNode*> rootNodes;

void tick(float deltaTime)
{
	for each (SceneNode* node in rootNodes)
	{
		node->tick(deltaTime);
	}
}

void draw (float deltaTime, sf::RenderWindow* target)
{
	for each (SceneNode* node in rootNodes)
	{
		node->superDraw(deltaTime, target);
	}
}

int main()
{
	sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode(720, 720), "SFML works!");

	sf::Clock clock;

	SceneNode* baseView = new SceneNode();

	TestChar* newChar = new TestChar();

	newChar->initSprite();

	baseView->addNode(newChar);

	rootNodes.push_back(baseView);

	while (window->isOpen())
	{
		sf::Event event;

		while (window->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window->close();
			}

		}

		sf::Time elapsed = clock.restart();

		float cachedTime = elapsed.asSeconds();

		while(elapsed.asSeconds() > 0)
		{
			elapsed = elapsed - sf::seconds(TIMESTEP);

			tick(TIMESTEP);
		}

		window->clear();

		draw(cachedTime, window);

		window->display();
	}

	for each (SceneNode* node in rootNodes)
	{
		delete node;
	}

	delete window;

	return 0;
}