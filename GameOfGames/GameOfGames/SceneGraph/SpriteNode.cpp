#include "SpriteNode.h"

SpriteNode::SpriteNode()
{
	if (texture.loadFromFile("caipira.png"))
	{
		texture.setSmooth(true);

		sprite.setTexture(texture);

		updateSprite();
	}
}

void SpriteNode::updateSprite()
{
	sprite.setPosition(getWorldLocation());//TODO calculate correct location based on window site and internal resolution 
	sprite.setScale(getTotalScale());//and scale
	sprite.setRotation(getTotalRotation());
}

void SpriteNode::transformUpdated()
{
	updateSprite();
	SceneNode::transformUpdated();
}

void SpriteNode::draw(float deltaTime, sf::RenderWindow* target)
{
	target->draw(sprite);

	SceneNode::draw(deltaTime, target);
}
