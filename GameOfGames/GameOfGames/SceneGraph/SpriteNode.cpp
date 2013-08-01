#include "SpriteNode.h"

SpriteNode::SpriteNode()
{
}

void SpriteNode::setTexture(sf::Texture newTexture)
{
	texture = newTexture;

	sprite.setTexture(texture);
}

void SpriteNode::onDraw(float deltaTime, sf::RenderWindow* target,  sf::Transform totalTransform)
{
	target->draw(sprite,totalTransform);
}
