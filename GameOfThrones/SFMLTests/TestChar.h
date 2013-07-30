#pragma once
#include "SceneNode.h"

class TestChar : public SceneNode
{
public:
	TestChar();
	void draw(float deltaTime, sf::RenderWindow* target);

private:
	sf::Texture texture;
	sf::Sprite sprite;
};