#include "SpriteNode.h"
#include "..\\AssetManager.h"
SpriteNode::SpriteNode()
{
	sprite = new sf::Sprite();
}

void SpriteNode::setTexture(sf::Texture* newTexture)
{
	texture = newTexture;

	sprite->setTexture((*texture));
}

void SpriteNode::onDraw(float deltaTime, sf::RenderWindow* target,  sf::Transform totalTransform)
{
	target->draw(*sprite,totalTransform);
}

SpriteNode::~SpriteNode(void)
{
	AssetManager::unsubscribeToTexture(texture);

	delete sprite;
}
