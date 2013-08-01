#pragma once
#include "SceneNode.h"

class SpriteNode : public SceneNode
{
public:
	SpriteNode();
	void setSprite(std::string newSource);
	void setTexture(sf::Texture newTexture);
	void onDraw(float deltaTime, sf::RenderWindow* target,  sf::Transform parentTranform);

private:
	sf::Sprite sprite;
	sf::Texture texture;
};