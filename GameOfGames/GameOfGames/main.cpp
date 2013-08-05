#include <iostream>
#include <vector>

#include <SFML/Graphics.hpp>
#include "SceneGraph/SpriteNode.h"
#include "SceneGraph/UIView.h"
#include "SceneGraph/SpriteNode.h"
#include "AssetManager.h"
#include "OptionsManager.h"
#include "UIViewClickListener.h"
#include "InputHandlerSFML.h"

#define TIMESTEP 0.01666666666f
#define WINDOW_TITLE "Game of Thrones"

std::vector<SceneNode*> rootNodes;


void testingShit()
{
	SceneNode* baseView = new SceneNode();

	SpriteNode* newChar = new SpriteNode();

	UIView* panel = new UIView(new sf::Vector2i(300,200),"Tileset.png");//this image has a transparent border of 

	//panel->removeTexture();
	//panel->setTintColor(255,0,0);
	//panel->setAlpha(0.5);
	//panel->resetTintColor();

	//newChar->setScale(sf::Vector2f(2.f,2.f));
	//newChar->setRotation(90.f);

	/*SpriteNode* miniChar = new SpriteNode();

	SpriteNode* third = new SpriteNode();*/

	newChar->setTexture("Tileset.png");
	/*miniChar->setTexture("chines.png");
	third->setTexture("caipira.png");*/

	//newChar->removeTexture();

	baseView->addNode(newChar,sf::Vector2f(0.f,0.f));
	baseView->addNode(panel,sf::Vector2f(0.f,45.f));
	/*baseView->addNode(miniChar,sf::Vector2f(125.f,0.f));
	baseView->addNode(third,sf::Vector2f(150.f,0.f));*/

	rootNodes.push_back(baseView);
}

int main()
{
	OptionsManager* manager = new OptionsManager();
	InputHandlerSFML* input = InputHandlerSFML::getInstance();

	sf::Vector2f displayResolution = manager->getDisplayResolution();
	sf::RenderWindow* window;
	if(manager->getFullscreen())
	{
		window = new sf::RenderWindow(sf::VideoMode(int(displayResolution.x), int(displayResolution.y)), WINDOW_TITLE, sf::Style::Fullscreen);
	}
	else
	{
		window = new sf::RenderWindow(sf::VideoMode(int(displayResolution.x),int(displayResolution.y)), WINDOW_TITLE);
	}
	window->setVerticalSyncEnabled((manager->getVSync() ?  true : false));

	//tests yo
	testingShit();

	sf::Clock clock;
	float remainingTime = 0;

	for(SceneNode* rootNode : rootNodes)
	{
		rootNode->setScale(*manager->getCachedScreenRatio());
	}

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

		input->poll();

		AssetManager::getIntance()->clearClickables();

		while(timeToConsume >= TIMESTEP)
		{
			timeToConsume -= TIMESTEP;

			for(SceneNode* node : rootNodes)
			{
				node->tick(TIMESTEP);				
			}
		}

		if(mouseButtonLeft == (mouseButtonLeft & input->getKeysPressed()))
		{
			std::cout<<"click\n";
		}

		if(mouseButtonLeft == (mouseButtonLeft & input->getKeysHeld()))
		{
			std::cout<<"held\n";
		}

		if((mouseButtonLeft == (mouseButtonLeft & input->getKeysHeld())) && (mouseButtonLeft == (mouseButtonLeft & input->getKeysPressed())))
		{
			std::cout<<"click and held\n";
		}

		remainingTime = timeToConsume;

		window->clear();

		for(SceneNode* node : rootNodes)
		{
			node->draw(cachedTime-remainingTime, window, sf::Transform());
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