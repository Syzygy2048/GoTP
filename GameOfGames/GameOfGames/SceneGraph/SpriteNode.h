#pragma once
#include "SceneNode.h"

class SpriteNode : public SceneNode
{
public:
	SpriteNode();
	void draw(float deltaTime, sf::RenderWindow* target);
	void setSprite(std::string newSource);
	void setTexture(sf::Texture newTexture);

protected:
	void transformUpdated();

private:
	void updateSprite();
	sf::Sprite sprite;
	sf::Texture texture;
};