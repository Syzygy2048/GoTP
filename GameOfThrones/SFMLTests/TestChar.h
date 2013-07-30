#pragma once
#include "SceneNode.h"

class TestChar : public SceneNode
{
public:
	void initSprite();
	void draw(float deltaTime, sf::RenderWindow* target);

private:
	sf::Texture texture;
	sf::Sprite sprite;
};