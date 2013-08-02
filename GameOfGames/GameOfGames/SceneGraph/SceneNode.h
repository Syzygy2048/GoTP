#pragma once
#include <vector>
#include <iostream>
#include <SFML/Graphics.hpp>

class SceneNode
{
public:

	//Override and dont forget to call the parent implementation.
	virtual void tick(float deltaTtime);
	virtual void onDraw(float deltaTime, sf::RenderWindow* target,  sf::Transform parentTranform);
	
	void draw(float deltaTime, sf::RenderWindow* target, sf::Transform parentTranform);
	void draw(float deltaTime, sf::RenderWindow* target);

	void setScreenRatio(sf::Vector2f newRatio);

	void setLayer(int newLayer);
	void move(sf::Vector2f newLocation);
	void setLocation(sf::Vector2f newLocation);
	void scale(sf::Vector2f newScale);
	void setScale(sf::Vector2f newScale);
	void setRotation(float newRotation);
	void setTransform(sf::Transform newTransform);

	//Call this to read the transform.
	sf::Transform getTransform();

	void addNode(SceneNode* node, sf::Vector2f location);

	SceneNode();
	~SceneNode(void);

protected:
	SceneNode* parent;
	//sf::Vector2f* screenRatio;//cant declare, otherwise second child wont appear
	std::vector<SceneNode*> children;

private:
	sf::Vector2f* cachedLocation;//had to make a pointer, or else children nodes would not render
	float cachedRotation;
	sf::Vector2f cachedScale;
	sf::Transform transform;
};
