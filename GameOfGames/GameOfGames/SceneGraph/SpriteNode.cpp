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

	onSetTexture();
}

void SpriteNode::onSetTexture()
{
	sprite->setTexture((*texture));
}

void SpriteNode::onDraw(float deltaTime, sf::RenderWindow* target,  sf::Transform totalTransform)
{
	target->draw(*sprite,totalTransform);
}

void SpriteNode::setTintColor(int red, int green, int blue, float alpha)
{
	sprite->setColor(sf::Color(red,green,blue,sf::Uint8(254*alpha)));
}

void SpriteNode::setTintColor(int red, int green, int blue)
{
	float alpha = getTintColor().a/254.f;

	setTintColor(red,green,blue,alpha);
}

void SpriteNode::setTintColor(sf::Color newColor)
{
	sprite->setColor(newColor);
}

void SpriteNode::setAlpha(float alpha)
{
	sf::Color c = getTintColor();

	c.a = sf::Uint8(255*alpha);

	sprite->setColor(c);
}

void SpriteNode::resetTintColor()
{
	sprite->setColor(sf::Color(255,255,255,255));
}

sf::Color SpriteNode::getTintColor()
{
	return sprite->getColor();
}

void SpriteNode::removeTexture()
{
	AssetManager::unsubscribeToTexture(texture);

	texture = NULL;

	onRemoveTexture();
}

SpriteNode::~SpriteNode(void)
{
	if (texture)
	{
		AssetManager::unsubscribeToTexture(texture);
	}

	delete sprite;
}
