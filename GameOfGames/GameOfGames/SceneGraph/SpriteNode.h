#pragma once
#include "SceneNode.h"

class SpriteNode : public SceneNode
{
public:
	void setSprite(std::string newSource);
	void setTexture(std::string textureName);
	void onDraw(float deltaTime, sf::RenderWindow* target, sf::Transform parentTranform);

	SpriteNode();
	~SpriteNode(void);

private:
	sf::Sprite* sprite;
	sf::Texture* texture;
};