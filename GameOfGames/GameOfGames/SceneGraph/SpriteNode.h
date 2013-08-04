#pragma once
#include "SceneNode.h"

class SpriteNode : public SceneNode
{
public:
	void setTexture(std::string textureName);
	void removeTexture();
	
	SpriteNode();
	~SpriteNode(void);

protected:
	virtual void onDraw(float deltaTime, sf::RenderWindow* target, sf::Transform parentTranform);
	virtual void onRemoveTexture(){};
	virtual void onSetTexture();
	sf::Sprite* sprite;
	sf::Texture* texture;
};