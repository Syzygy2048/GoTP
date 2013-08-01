#include "SpriteNode.h"

SpriteNode::SpriteNode()
{
	updateSprite();
}

void SpriteNode::setTexture(sf::Texture newTexture)
{
	texture = newTexture;

	sprite.setTexture(texture);
}

void SpriteNode::updateSprite()
{
	//sprite.setOrigin(-getWorldLocation());

	//sprite.setPosition(getWorldLocation());//TODO calculate correct location based on window site and internal resolution 
	//sprite.setScale(getTotalScale());//and scale
	//sprite.setRotation(getTotalRotation());
	//std::cout << sprite.getOrigin().x<< ", "<<sprite.getOrigin().y << " for location:"<< sprite.getPosition().x<<" ,"<<sprite.getPosition().y<< "\n";
}

void SpriteNode::transformUpdated()
{
	updateSprite();
	SceneNode::transformUpdated();
}

void SpriteNode::draw(float deltaTime, sf::RenderWindow* target)
{
	target->draw(sprite,getWorldTransform());

	SceneNode::draw(deltaTime, target);
}
