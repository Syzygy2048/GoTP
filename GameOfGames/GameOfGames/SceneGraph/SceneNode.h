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

	//For caching purposes, Ive made so you MUST call the setters. The setters call the transformUpdated method. 
	//If I were to allow for the transform to be directly set, one could misuse the framework.
	void setLayer(int newLayer);
	void setLocation(sf::Vector2f newLocation);
	void setScale(sf::Vector2f newScale);
	void setRotation(float newRotation);
	void setTransform(sf::Transform newTransform);

	//Call this to read the transform.
	sf::Transform getTransform();

	void addNode(SceneNode* node, sf::Vector2f location);

	SceneNode();
	~SceneNode(void);

protected:
	//Override and dont forget to call the parent implementation.
	virtual void transformUpdated();
	
	SceneNode* parent;
	std::vector<SceneNode*> children;

private:
	float cachedRotation;
	sf::Transform transform;
};
