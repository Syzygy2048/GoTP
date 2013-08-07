#include <iostream>
#include <vector>

#include <SFML/Graphics.hpp>
#include "SceneGraph/SpriteNode.h"
#include "SceneGraph/UIView.h"
#include "SceneGraph/SpriteNode.h"
#include "AssetManager.h"
#include "OptionsManager.h"
#include "TestClickListener.h"
#include "UIViewListener.h"
#include "InputHandlerSFML.h"

#define TIMESTEP 0.01666666666f
#define WINDOW_TITLE "Game of Thrones"

std::vector<SceneNode*> rootNodes;

void testingShit()
{
	SceneNode* baseView = new SceneNode();

	SpriteNode* newChar = new SpriteNode();
	newChar->setTexture("Tileset.png");

	TestClickListener* viewListener = new TestClickListener();

	UIView* panel = new UIView(new sf::Vector2i(300,200),"Tileset.png");//this image has a transparent border of 
	UIView* panel2 = new UIView(new sf::Vector2i(150,100),"Tileset.png");//this image has a transparent border of 

	panel->setHoverable(true);
	panel2->setHoverable(true);

	panel->setUIViewListener(viewListener);
	panel2->setUIViewListener(viewListener);

	//panel->removeTexture();
	//panel->setTintColor(255,0,0);
	//panel->setAlpha(0.5);
	//panel->resetTintColor();

	//newChar->setScale(sf::Vector2f(2.f,2.f));
	//newChar->setRotation(45.f);

	/*SpriteNode* miniChar = new SpriteNode();

	SpriteNode* third = new SpriteNode();*/

	
	/*miniChar->setTexture("chines.png");
	third->setTexture("caipira.png");*/

	//newChar->removeTexture();

	//panel2->setRotation(45.f);

	//baseView->addNode(newChar,sf::Vector2f(0.f,0.f));
	baseView->addNode(panel,sf::Vector2f(150.f,100.f));
	baseView->addNode(panel2,sf::Vector2f(75.f,250.f));

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

		input->poll(window);

		AssetManager::getInstance()->clearClickable();

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
			node->draw(cachedTime-remainingTime, window, sf::Transform());
		}

		
		AssetManager::getInstance()->checkOnClickable();
		

		window->display();
	}

	for(SceneNode* node : rootNodes)
	{
		delete node;
	}
	delete window;

	return 0;
}