#include <iostream>
#include <string>
#include <vector>

#include <SFML/Graphics.hpp>
#include "SceneGraph\SpriteNode.h"
#include "SceneGraph\UIView.h"
#include "SceneGraph\SceneNode.h"
#include "SceneGraph\SpriteNode.h"
#include "AssetManager.h"
#include "OptionsManager.h"
#include "TestClickListener.h"
#include "UIViewListener.h"
#include "InputHandlerSFML.h"

#define TIMESTEP 0.01666666666f
#define WINDOW_TITLE "Game of Thrones"

std::vector<SceneNode*> rootNodes;
UIView* fpsCounter;

void testingShit()
{
	SceneNode* baseView = new SceneNode();

	//SpriteNode* newChar = new SpriteNode();
	//newChar->setTexture("Tileset.png");

	TestClickListener* viewListener = new TestClickListener();

	UIView* panel = new UIView(new sf::Vector2i(300,200),"Tileset.png");//this image has a transparent border of 
	UIView* panel2 = new UIView(new sf::Vector2i(150,100),"Tileset.png");//this image has a transparent border of 

	fpsCounter = new UIView(new sf::Vector2i(50,50));

	fpsCounter ->setOffSet(new sf::Vector2i(25,25));


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
	baseView->addNode(fpsCounter,sf::Vector2f(0.f,0.f));

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

	InputHandlerSFML::getInstance()->informMouseMoved(sf::Mouse::getPosition(*window));

	int framesDrawn = 0;

	float fpsClock = 0.f;

	while(window->isOpen())
	{
		if (fpsClock >=1)
		{
			fpsClock -= 1;

			int tempFrames = framesDrawn;

			sf::Font font = sf::Font();

			font.loadFromFile("arial.ttf");

			if(manager->getShowFps())
			{
				char numstr[10];

				sprintf_s(numstr, "%i", framesDrawn);

				sf::String newText = sf::String(numstr);

				sf::Text* text = new sf::Text(newText, font);

				text->setCharacterSize(20);

				text->setColor(sf::Color::Red);

				fpsCounter->setText(text);

				framesDrawn = 0;
			}
			else if(fpsCounter->getText())
			{
				delete fpsCounter->getText();
			}
		}

		sf::Event event;

		InputHandlerSFML::getInstance()->clearOcurredEvents();

		while(window->pollEvent(event))
		{
			switch(event.type)
			{
			case sf::Event::MouseButtonPressed :
				{
					InputHandlerSFML::getInstance()->informMouseClicked(event.key.code);
					break;
				}
			case sf::Event::MouseMoved:
				{
					InputHandlerSFML::getInstance()->informMouseMoved(sf::Mouse::getPosition(*window));
					break;
				}
			case sf::Event::Closed :
				{
					window->close();

					break;
				}
			}
		}

		sf::Time elapsed = clock.restart();
		fpsClock += elapsed.asSeconds();
		float timeToConsume = remainingTime + elapsed.asSeconds();
		float cachedTime = timeToConsume;

		InputHandlerSFML::getInstance()->clearClickable();

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

		framesDrawn ++;

		InputHandlerSFML::getInstance()->checkOnClickable();

		window->display();
	}

	for(SceneNode* node : rootNodes)
	{
		delete node;
	}

	delete window;

	return 0;
}