#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "SceneNode.h"
#include "SpriteNode.h"

#define TIMESTEP 0.01666666666f
#define WINDOW_TITLE "Game of Thrones, Literally!"

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
		node->draw(deltaTime, target);
	}
}

int main()
{
	sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode(1280, 720), WINDOW_TITLE);//TODO use the window configuration
	sf::Clock clock;

	SceneNode* baseView = new SceneNode();
	SpriteNode* newChar = new SpriteNode();

	baseView->addNode(newChar,sf::Vector2f(20.f,20.f));//DUMMY LINE
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