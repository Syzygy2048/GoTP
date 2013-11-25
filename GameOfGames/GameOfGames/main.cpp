#include <iostream>
#include <string>
#include <vector>

#include "Box2D\Box2D.h"
#include "Enums.h"
#include <SFML/Graphics.hpp>
#include "FocusGroup.h"
#include "SceneGraph\SpriteNode.h"
#include "SceneGraph\UIView.h"
#include "SceneGraph\SceneNode.h"
#include "SceneGraph\SpriteNode.h"
#include "AssetManager.h"
#include "OptionsManager.h"
#include "TestClickListener.h"
#include "UIViewListener.h"
#include "MainNodesManager.h"
#include "InputHandlerSFML.h"


#define TIMESTEP 0.01666666666f
#define WINDOW_TITLE "Game of Thrones"

std::vector<SceneNode*> rootNodes;


UIView* fpsCounter;
sf::RenderWindow* window;
OptionsManager* manager;
InputHandlerSFML* inputHandler;
MainNodesManager* baseNodesManager;

void testingShit()
{
	//SpriteNode* newChar = new SpriteNode();
	//newChar->setTexture("Tileset.png");
	std::vector<FocusGroup*>* focusGroups;
	FocusGroup* group;
	FocusGroup* group2;

	TestClickListener* viewListener = new TestClickListener();

	UIView* panel = new UIView(new sf::Vector2i(150,100),"Tileset.png");//this image has a transparent border of 
	UIView* panel2 = new UIView(new sf::Vector2i(150,100),"Tileset.png");//this image has a transparent border of 
	UIView* panel3 = new UIView(new sf::Vector2i(150,100),"Tileset.png");//this image has a transparent border of 
	UIView* panel4 = new UIView(new sf::Vector2i(150,100),"Tileset.png");//this image has a transparent border of 

	//panel->setHoverable(true);
	//panel2->setHoverable(true);
	//panel3->setHoverable(true);
	//panel4->setHoverable(true);

	panel->setUIViewListener(viewListener);
	panel->setDrawAsPanel(true);
	panel2->setDrawAsPanel(true);
	panel2->setUIViewListener(viewListener);

	panel3->setUIViewListener(viewListener);
	panel3->setDrawAsPanel(true);
	panel4->setDrawAsPanel(true);
	panel4->setUIViewListener(viewListener);

	group = new FocusGroup();
	group2 = new FocusGroup();

	focusGroups = new std::vector<FocusGroup*>();

	focusGroups->push_back(group);
	focusGroups->push_back(group2);


	//group->setLooped(false);
	group->setOrientation(GroupOrientation::VERTICAL);
	group2->setOrientation(GroupOrientation::VERTICAL);

	group->insertFocusable(panel);
	group->insertFocusable(panel2);

	group2->insertFocusable(panel3);
	group2->insertFocusable(panel4);

	InputHandlerSFML::getInstance()->setFocusGroupSet(focusGroups);
	group2->selectFocusable(panel3);

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

	panel->setOffSet(new sf::Vector2i(75,50));
	panel2->setOffSet(new sf::Vector2i(75,50));
	panel3->setOffSet(new sf::Vector2i(75,50));
	panel4->setOffSet(new sf::Vector2i(75,50));

	SceneNode* baseView = baseNodesManager->getRootNode(RootNodeType::HUD);

	baseView->addNode(panel,sf::Vector2f(0.f,0.f));
	baseView->addNode(panel2,sf::Vector2f(0.f,100.f));

	baseView->addNode(panel3,sf::Vector2f(150.f,0.f));
	baseView->addNode(panel4,sf::Vector2f(150.f,100.f));

	/*baseView->addNode(miniChar,sf::Vector2f(125.f,0.f));
	baseView->addNode(third,sf::Vector2f(150.f,0.f));*/
}

void initWindow()
{
	if (window)
	{
		delete window;
	}

	sf::Vector2f displayResolution = manager->getDisplayResolution();

	if(manager->getFullscreen())
	{
		window = new sf::RenderWindow(sf::VideoMode(int(displayResolution.x), int(displayResolution.y)), WINDOW_TITLE, sf::Style::Fullscreen);
	}
	else
	{
		window = new sf::RenderWindow(sf::VideoMode(int(displayResolution.x),int(displayResolution.y)), WINDOW_TITLE);
	}

	window->setVerticalSyncEnabled((manager->getVSync() ? true : false));

	manager->setWindowInstance(window);
	manager->informWindowReloaded();
}

int main()
{
	manager = OptionsManager::getInstance();
	inputHandler = InputHandlerSFML::getInstance();

	initWindow();

	SceneNode* bgNode = new SceneNode();
	SceneNode* scenarioNode = new SceneNode();
	SceneNode* hudNode = new SceneNode();

	baseNodesManager = MainNodesManager::getInstance();

	baseNodesManager->setRootNode(bgNode, RootNodeType::BACKGROUND);
	baseNodesManager->setRootNode(scenarioNode, RootNodeType::SCENARIO);
	baseNodesManager->setRootNode(hudNode,RootNodeType::HUD);

	fpsCounter = new UIView(new sf::Vector2i(100,50));

	//Base elements. HUD, scenario, etc.
	rootNodes.push_back(bgNode);
	rootNodes.push_back(scenarioNode);
	rootNodes.push_back(hudNode);
	rootNodes.push_back(fpsCounter);

	sf::Font font = sf::Font();

	font.loadFromFile("Assets/Fonts/arial.ttf");

	sf::Text* text = new sf::Text("", font);

	text->setCharacterSize(30);

	text->setColor(sf::Color::Red);

	fpsCounter->setText(text);

	fpsCounter->setOffSet(new sf::Vector2i(55,25));

	//tests yo
	testingShit();

	fpsCounter->setIgnoreMouse(true);

	sf::Clock clock;

	float remainingTime = 0;

	for(SceneNode* rootNode : rootNodes)
	{
		rootNode->setScale(*manager->getCachedScreenRatio());
	}

	inputHandler->informMouseMoved(sf::Mouse::getPosition(*window));

	int framesDrawn = 0;
	float minimumTimeBetweenDpadInputs = 0.02f;
	float timeSinceLastDpadInput = minimumTimeBetweenDpadInputs;
	float fpsClock = 0.f;

	while(window->isOpen() || manager->getOptionsChanged())
	{
		if(!window->isOpen() && manager->getOptionsChanged())
		{
			initWindow();

			for(SceneNode* rootNode : rootNodes)
			{
				rootNode->setScale(*manager->getFinalScreenRatio());
			}
		}

		if (fpsClock >=1)
		{
			fpsClock -= 1;

			int tempFrames = framesDrawn;

			if(manager->getShowFps())
			{
				char numstr[10];

				sprintf_s(numstr, "%i", framesDrawn);

				fpsCounter->updateText(sf::String(numstr));

				framesDrawn = 0;
			}
			else
			{
				fpsCounter->updateText("");
			}
		}

		sf::Event event;

		inputHandler->clearOcurredEvents();

		float previousHdPad =0;
		float previousVdPad =0;

		while(window->pollEvent(event))
		{
			switch(event.type)
			{
			case sf::Event::MouseButtonPressed :
				{
					inputHandler->informMouseClicked(event.key.code);
					break;
				}
			case sf::Event::KeyPressed:
				{
					if(sf::Keyboard::A == event.key.code)
					{
						inputHandler->informDpadChanged(LEFT);
					}
					else if (sf::Keyboard::W == event.key.code)
					{
						inputHandler->informDpadChanged(UP);
					}
					else if (sf::Keyboard::D == event.key.code)
					{
						inputHandler->informDpadChanged(RIGHT);
					}
					else if (sf::Keyboard::S == event.key.code)
					{
						inputHandler->informDpadChanged(DOWN);
					}
					else if (sf::Keyboard::Return == event.key.code)
					{
						inputHandler->informConfirmPressed(ConfirmSource::KEYBOARD,event.key.code);
					}
					break;
				}
			case sf::Event::MouseMoved:
				{
					inputHandler->informMouseMoved(sf::Mouse::getPosition(*window));
					break;
				}
			case sf::Event::Closed :
				{
					window->close();

					break;
				}
			case sf::Event::MouseLeft:
				{
					inputHandler->informMouseMoved(sf::Vector2i(-1,-1));
					break;
				}
			case sf::Event::JoystickButtonPressed:
				{
					inputHandler->informConfirmPressed(ConfirmSource::JOYSTICK,event.key.code);

					break;
				}
			case sf::Event::JoystickMoved:
				{
					//information regarding 360 controller
					//sf::Joystick::getAxisPosition(0, sf::Joystick::Z) triggers, left one is the positive.
					//horizontal and vertical.
					//X  Y left analog
					//U  R right analog
					//PovY PovX d-pad

					if(timeSinceLastDpadInput >= minimumTimeBetweenDpadInputs)
					{
						timeSinceLastDpadInput = 0.f;

						if(previousHdPad > -100 && sf::Joystick::getAxisPosition(0, sf::Joystick::PovY) == -100 )
						{
							inputHandler->informDpadChanged(LEFT);
						}

						else if(previousHdPad < 100 && sf::Joystick::getAxisPosition(0, sf::Joystick::PovY) == 100 )
						{
							inputHandler->informDpadChanged(RIGHT);
						}

						if(previousVdPad > -100 && sf::Joystick::getAxisPosition(0, sf::Joystick::PovX) == -100 )
						{
							inputHandler->informDpadChanged(DOWN);
						}
						else if(previousVdPad < 100 && sf::Joystick::getAxisPosition(0, sf::Joystick::PovX) == 100 )
						{
							inputHandler->informDpadChanged(UP);
						}
					}

					previousHdPad = sf::Joystick::getAxisPosition(0, sf::Joystick::PovY);
					previousVdPad = sf::Joystick::getAxisPosition(0, sf::Joystick::PovX);

					break;
				}
			}
		}

		sf::Time elapsed = clock.restart();
		fpsClock += elapsed.asSeconds();

		if(timeSinceLastDpadInput <= minimumTimeBetweenDpadInputs)
		{
			timeSinceLastDpadInput += elapsed.asSeconds();
		}

		inputHandler->setMouseInteractive(NULL);

		/*float timeToConsume = remainingTime + elapsed.asSeconds();
		float cachedTime = timeToConsume;

		while(timeToConsume >= TIMESTEP)
		{

		timeToConsume -= TIMESTEP;

		for(SceneNode* node : rootNodes)
		{
		node->tick(TIMESTEP);				
		}
		}

		remainingTime = timeToConsume;*/

		for(SceneNode* node : rootNodes)
		{
			node->tick(elapsed.asSeconds());				
		}

		window->clear();

		for(SceneNode* node : rootNodes)
		{
			node->draw(elapsed.asSeconds(), window, sf::Transform());
		}

		framesDrawn ++;

		inputHandler->checkOnMouseInteractive();

		window->display();

		if(manager->getOptionsChanged())
		{
			window->close();
		}
	}

	for(SceneNode* node : rootNodes)
	{
		delete node;
	}

	delete window;
	delete baseNodesManager;
	delete inputHandler;
	delete manager;

	return 0;
}