#pragma once
#include <SFML\Graphics.hpp>
#include "SpriteNode.h"
#include "..\InputHandlerSFML.h"
#include "..\UIViewClickListener.h"

class UIView:public SpriteNode
{

public:
	const sf::Vector2i* getSize(){ return size; };
	void setSize(sf::Vector2i* newSize);
	void setClickListener(UIViewClickListener* newListener);
	void activated();
	bool getFocusable(){ return focusable;}
	void setFocusable(bool newFocusable){ focusable = newFocusable; }

	UIView(sf::Vector2i* newSize);
	UIView(sf::Vector2i* newSize, std::string newTexture);
	~UIView(void);

protected:
	virtual void onDraw(float deltaTime, sf::RenderWindow* target, sf::Transform parentTranform);
	virtual void onRemoveTexture();
	virtual void onSetTexture();

private:
	bool focusable;
	UIViewClickListener* listener;
	sf::Texture* finalTexture;
	virtual void adjustBackGround();
	sf::Vector2i* size;
};