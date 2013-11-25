#include "TestClickListener.h"
#include "SceneGraph\UIView.h"
#include "SFML\Graphics.hpp"
#include "OptionsManager.h"
#include "FocusGroup.h"

void TestClickListener::viewHovered(UIView* sender, bool hoveredState)
{
	if (hoveredState)
	{
		sender->setTintColor(255,128,128);
	}
	else
	{
		sender->resetTintColor();
	}
}

void TestClickListener::viewFocused(UIView* sender, bool focusedState)
{
	if (focusedState)
	{
		if(sender->getFocusGroup()->getActive())
		{
			sender->setTintColor(255,50,128);
		}
		else
		{
			sender->setTintColor(255,128,128);
		}
	}
	else
	{
		if(sender->getFocusGroup()->getActive())
		{
			sender->resetTintColor();
		}
		else
		{
			sender->setTintColor(255,128,128);
		}
	}
}

void TestClickListener::viewSelected(UIView* sender, ConfirmSource source, int key)
{
	if(source == ConfirmSource::MOUSE && key == sf::Mouse::Left
		|| source == ConfirmSource::KEYBOARD && key == sf::Keyboard::Return
		|| source == ConfirmSource::JOYSTICK && !key)
	{
		sf::Font font;

		font.loadFromFile("Assets/Fonts/arial.ttf");

		sf::Text* text = new sf::Text("hello", font);

		text->setCharacterSize(30);

		text->setStyle(sf::Text::Italic);

		text->setColor(sf::Color::Red);

		sender->setText(text);
	}
}