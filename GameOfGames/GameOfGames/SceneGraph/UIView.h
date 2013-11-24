#pragma once
#include "SpriteNode.h"
#include <SFML\Graphics.hpp>

class FocusGroup;
class UIViewListener;

class UIView:public SpriteNode
{
public:
	//constructors and destructor

	UIView(sf::Vector2i* newSize, std::string newTexture);
	UIView(sf::Vector2i* newSize);
	~UIView(void);

	void setFocusGroup(FocusGroup* newGroup){group = newGroup;}
	FocusGroup* getFocusGroup(){return group;}

	void setUIViewListener(UIViewListener* newListener);

	//methods about its behaviour status
	void activated(int key);
	bool getFocusable(){ return focusable;}

	//Being on focus means a focus group focused this view.
	void setFocusedState(bool newFocusState);

	//Being focusable means it can be hovered or clicked, but it doesnt means it wont block the mouse when hovering something under this view.
	void setFocusable(bool newFocusable){ focusable = newFocusable; }
	bool getHoveredState(){ return beingHovered;}
	void setHoveredState(bool hoveredState);


	//Being hoverable means it will respond when the mouse is hovering this view.
	void setHoverable(bool newHoverable){ hoverable = newHoverable; }
	bool isHoverable(){ return hoverable;}


	//If set to ignore mouse, it wont get in the way of something being hovered by the mouse.
	void setIgnoreMouse(bool newIgnoreMouse){ignoreMouse = newIgnoreMouse;}
	bool ignoresMouse(){ return ignoreMouse;}

	//methods about how it draws

	//If drawn as a panel, it wont stretch is texture, insteading treating it as a tileset.
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
	
	bool focusedState;
	bool drawAsPanel;
	bool beingHovered;
	bool hoverable;
	bool ignoreMouse;
	bool focusable;
	bool alwaysUseClearBg;
	UIViewListener* listener;
	sf::Texture* finalTexture;
	virtual void adjustBackGround();
	sf::Vector2i* size;
	FocusGroup* group;
};