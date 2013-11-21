#include "TestClickListener.h"
#include "SceneGraph\UIView.h"
#include "SFML\Graphics.hpp"

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

void TestClickListener::viewClicked(UIView* sender, int key)
{
	if(key)
	{
		return;
	}

	sf::Font font;

	font.loadFromFile("arial.ttf");

	sf::Text* text = new sf::Text("hello", font);

	text->setCharacterSize(30);

	text->setStyle(sf::Text::Italic);

	text->setColor(sf::Color::Red);

	sender->setText(text);
}