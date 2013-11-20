#pragma once
#include <SFML\Graphics.hpp>
#include "SceneNode.h"

class SpriteNode : public SceneNode
{
public:
	//just pass the texture name, no need to pass the folder that contains it too
	void setTexture(std::string textureName);
	void removeTexture();
	void setOffSet(sf::Vector2i* newOffset);
	sf::Vector2i* getOffset(){ return offset; }
	void setTintColor(int red, int green, int blue, float alpha);
	void setTintColor(int red, int green, int blue);
	void setTintColor(sf::Color newColor);
	void setAlpha(float alpha);
	void resetTintColor();
	sf::Color getTintColor();

	SpriteNode();
	~SpriteNode(void);

protected:
	sf::Vector2i* offset;
	virtual void onDraw(float deltaTime, sf::RenderWindow* target, sf::Transform parentTranform);
	virtual void onRemoveTexture(){};
	virtual void onSetTexture();
	sf::Sprite* sprite;
	sf::Texture* texture;
};