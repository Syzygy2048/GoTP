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
	//set the object that is suposed to respond to a click on this view
	void setClickListener(UIViewClickListener* newListener);
	void activated();
	bool getFocusable(){ return focusable;}
	void setFocusable(bool newFocusable){ focusable = newFocusable; }//focusable == clickable, so far

	UIView(sf::Vector2i* newSize);
	UIView(sf::Vector2i* newSize, std::string newTexture);
	~UIView(void);

protected:
	//so I can cache the real area based on its size and the parent transform
	virtual void onDraw(float deltaTime, sf::RenderWindow* target, sf::Transform parentTranform, bool clickTest);
	virtual void onRemoveTexture();
	virtual void onSetTexture();

private:
	bool focusable;
	UIViewClickListener* listener;
	sf::Texture* finalTexture;
	virtual void adjustBackGround();
	sf::Vector2i* size;
};