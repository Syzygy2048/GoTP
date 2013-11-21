#pragma once
#include "SpriteNode.h"
#include <SFML\Graphics.hpp>

class UIViewListener;

class UIView:public SpriteNode
{
public:
	const sf::Vector2i* getSize(){ return size; };
	void setSize(sf::Vector2i* newSize);
	//set the object that is suposed to respond to a click on this view
	void setUIViewListener(UIViewListener* newListener);
	void activated(int key);
	bool getFocusable(){ return focusable;}
	void setFocusable(bool newFocusable){ focusable = newFocusable; }//focusable == any action that can be performed
	bool getHoveredState(){ return beingHovered;}
	void setHoveredState(bool hoveredState);
	void setHoverable(bool newHoverable){ hoverable = newHoverable; }
	bool isHoverable(){ return hoverable;}
	bool isDrawingAsPanel(){ return drawAsPanel; }
	void setAlwaysUseClearBg(bool newAlwaysUseClearBg){alwaysUseClearBg = newAlwaysUseClearBg; };
	void setDrawAsPanel(bool newDrawAsPanel);
	void setText(sf::Text* text);
	void setFont(sf::Font* font);
	sf::Font* getFont(){return font;};
	sf::Text* getText(){ return text; }
	
	UIView(sf::Vector2i* newSize, std::string newTexture);
	UIView(sf::Vector2i* newSize);
	~UIView(void);

protected:
	virtual void onDraw(float deltaTime, sf::RenderWindow* target, sf::Transform parentTranform);
	virtual void onRemoveTexture();
	virtual void onSetTexture();

private:
	void configInitialSettings(sf::Vector2i* newSize);

	sf::Font* font;
	sf::Text* text;
	bool drawAsPanel;
	bool beingHovered;
	bool hoverable;
	bool focusable;
	bool alwaysUseClearBg;
	UIViewListener* listener;
	sf::Texture* finalTexture;
	virtual void adjustBackGround();
	sf::Vector2i* size;
};