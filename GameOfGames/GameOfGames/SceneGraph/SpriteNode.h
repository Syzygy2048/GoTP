#pragma once
#include "SceneNode.h"

class SpriteNode : public SceneNode
{
public:
	SpriteNode();
	void draw(float deltaTime, sf::RenderWindow* target, sf::Transform parentTranform);
	void setSprite(std::string newSource);
	void setTexture(sf::Texture newTexture);

protected:
	void transformUpdated();

private:
	sf::Sprite sprite;
	sf::Texture texture;
};