#pragma once
#include "SceneNode.h"

class SpriteNode : public SceneNode
{
public:
	SpriteNode();
	void draw(float deltaTime, sf::RenderWindow* target);
	void setSprite(std::string newSource);
	void transformUpdated();

private:
	sf::Texture texture;
	sf::Sprite sprite;
};