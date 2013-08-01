#include "SpriteNode.h"

SpriteNode::SpriteNode()
{
}

void SpriteNode::setTexture(sf::Texture newTexture)
{
	texture = newTexture;

	sprite.setTexture(texture);
}

void SpriteNode::transformUpdated()
{
	SceneNode::transformUpdated();
}

void SpriteNode::draw(float deltaTime, sf::RenderWindow* target, sf::Transform parentTranform)
{
	sf::Transform totalTransform = parentTranform * transform;

	target->draw(sprite,totalTransform);

	SceneNode::draw(deltaTime, target, totalTransform);
}
