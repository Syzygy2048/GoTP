#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "Options\OptionsManager.h"
#include "SceneGraph/SceneNode.h"
#include "SceneGraph/SpriteNode.h"

#define TIMESTEP 0.01666666666f
#define WINDOW_TITLE "Game of Thrones"

std::vector<SceneNode*> rootNodes;

int main()
{
	OptionsManager* manager = new OptionsManager();

	sf::Vector2i displayResolution = manager->getDisplayResolution();

	sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode(displayResolution.x,displayResolution.y), WINDOW_TITLE);
	sf::Clock clock;

	SceneNode* baseView = new SceneNode();

	baseView->setScreenRatio(manager->getCachedScreenRatio());

	SpriteNode* newChar = new SpriteNode();

	SpriteNode* miniChar = new SpriteNode();

	sf::Texture* defTexture = new sf::Texture();
	sf::Texture* secondTexture = new sf::Texture();

	secondTexture->loadFromFile("Assets\\Sprites\\preto.png");
	defTexture->loadFromFile("Assets\\Sprites\\caipira.png");
	
	newChar->setTexture(defTexture);

	miniChar->setTexture(secondTexture);

	newChar->addNode(miniChar,sf::Vector2f(25.f,0.f));
	baseView->addNode(newChar,sf::Vector2f(100.f,0.f));

	miniChar->setScale(sf::Vector2f(2.f,1.f));

	miniChar->setLocation(sf::Vector2f(25.f,0.f));

	miniChar->scale(sf::Vector2f(0.5,1.f));

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