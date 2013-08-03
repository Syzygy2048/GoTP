#include "SpriteNode.h"
#include "..\\AssetManager.h"
SpriteNode::SpriteNode()
{
	sprite = new sf::Sprite();
}

void SpriteNode::setTexture(std::string textureName)
{
	sf::Texture* newTexture = AssetManager::getTexture(textureName);

	if(!newTexture)
	{
		std::cout<<"Received null texture for "<< textureName<<". \n";

		return;
	}

	if (texture)
	{
		AssetManager::unsubscribeToTexture(texture);
	}

	texture = newTexture;

	sprite->setTexture((*texture));
}

void SpriteNode::onDraw(float deltaTime, sf::RenderWindow* target,  sf::Transform totalTransform)
{
	target->draw(*sprite,totalTransform);
}

SpriteNode::~SpriteNode(void)
{
	if (texture)
	{
		AssetManager::unsubscribeToTexture(texture);
	}

	delete sprite;
}
