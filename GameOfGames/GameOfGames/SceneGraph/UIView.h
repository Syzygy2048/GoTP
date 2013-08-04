#pragma once
#include <SFML\Graphics.hpp>
#include "SpriteNode.h"

class UIView:public SpriteNode
{
public:
	const sf::Vector2i* getSize(){ return size; };
	void setSize(sf::Vector2i* newSize);

	UIView(sf::Vector2i* newSize, std::string newTexture);
	~UIView(void);
protected:
	virtual void onRemoveTexture();
	virtual void onSetTexture();

private:
	sf::Texture* finalTexture;
	void adjustBackGround();
	sf::Vector2i* size;
};