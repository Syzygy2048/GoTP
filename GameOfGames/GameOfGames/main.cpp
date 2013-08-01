#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "SceneGraph/SceneNode.h"
#include "SceneGraph/SpriteNode.h"
#include "InputHandlerSFML.h"

#define TIMESTEP 0.01666666666f
#define WINDOW_TITLE "Game of Thrones"

std::vector<SceneNode*> rootNodes;

int main()
{
	sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode(1280, 720), WINDOW_TITLE);//TODO use the window configuration
	sf::Clock clock;

	SceneNode* baseView = new SceneNode();
	SpriteNode* newChar = new SpriteNode();

	//newChar->setScale(sf::Vector2f(2.f,2.f));
	//newChar->setRotation(90.f);
	std::cerr << space << '\n';

	SpriteNode* miniChar = new SpriteNode();
	
	newChar->addNode(miniChar,sf::Vector2f(50.f,50.f));
	baseView->addNode(newChar,sf::Vector2f(50.f,50.f));
	rootNodes.push_back(baseView);

	float remainingTime = 0;

	while(window->isOpen())
	{
		sf::Event event;
		while(window->pollEvent(event))
		{
			if(event.type == sf::Event::Closed)
			{
				window->close();
			}
		}

		sf::Time elapsed = clock.restart();
		float timeToConsume = remainingTime + elapsed.asSeconds();
		float cachedTime = timeToConsume;

		while(timeToConsume >= TIMESTEP)
		{
			timeToConsume -= TIMESTEP;

			for(SceneNode* node : rootNodes)
			{
				node->tick(TIMESTEP);				
			}
		}

		remainingTime = timeToConsume;

		window->clear();

		for(SceneNode* node : rootNodes)
		{
			node->draw(cachedTime-remainingTime, window);
		}

		window->display();
	}

	for(SceneNode* node : rootNodes)
	{
		delete node;
	}
	delete window;

	return 0;
}