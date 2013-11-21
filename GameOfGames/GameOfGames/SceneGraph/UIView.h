#pragma once
#include "SpriteNode.h"
#include <SFML\Graphics.hpp>

class UIViewListener;

class UIView:public SpriteNode
{
public:
	//constructors and destructor
	UIView(sf::Vector2i* newSize, std::string newTexture);
	UIView(sf::Vector2i* newSize);
	~UIView(void);

	//set the object that is suposed to respond to a click on this view
	void setUIViewListener(UIViewListener* newListener);

	//methods about its behaviour status
	void activated(int key);
	bool getFocusable(){ return focusable;}
	void setFocusable(bool newFocusable){ focusable = newFocusable; }//focusable == any action that can be performed
	bool getHoveredState(){ return beingHovered;}
	void setHoveredState(bool hoveredState);
	void setHoverable(bool newHoverable){ hoverable = newHoverable; }
	bool isHoverable(){ return hoverable;}

	//methods about how it draws
	void setDrawAsPanel(bool newDrawAsPanel);
	bool isDrawingAsPanel(){ return drawAsPanel; }
	void setAlwaysUseClearBg(bool newAlwaysUseClearBg){alwaysUseClearBg = newAlwaysUseClearBg; };

	//methods about its text
	void setText(sf::Text* text);
	void updateText(sf::String newString);
	const sf::Text* getText(){ return text; }

	//methods about its size
	const sf::Vector2i* getSize(){ return size; };
	void setSize(sf::Vector2i* newSize);

protected:
	//methods called by other parent and children
	virtual void onDraw(float deltaTime, sf::RenderWindow* target, sf::Transform parentTranform);
	virtual void onRemoveTexture(){adjustBackGround();};
	virtual void onSetTexture(){adjustBackGround();};

private:
	void configInitialSettings(sf::Vector2i* newSize);

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