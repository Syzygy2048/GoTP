#pragma once
#include "SceneNode.h"

class SpriteNode : public SceneNode
{
public:
	SpriteNode();
	void draw(float deltaTime, sf::RenderWindow* target);
	void setSprite(std::string newSource);

protected:
	void transformUpdated();

private:
	void updateSprite();
	sf::Texture texture;
	sf::Sprite sprite;
};