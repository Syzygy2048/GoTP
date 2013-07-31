#pragma once
#include <vector>
#include <iostream>
#include <SFML/Graphics.hpp>

class SceneNode
{
public:

	//
	struct Transform
	{
		float rotation;
		int layer;
		sf::Vector2f location;
		sf::Vector2f scale;
	};

	//Override and dont forget to call the parent implementation.
	virtual void tick(float deltaTtime);
	virtual void draw(float deltaTime, sf::RenderWindow* target);
	virtual void transformUpdated();

	sf::Vector2f getWorldLocation();
	sf::Vector2f getTotalScale();
	float getTotalRotation();

	//For caching purposes, Ive made so you MUST call the setters. The setters call the transformUpdated method. 
	//If I were to allow for the transform to be directly set, one could misuse the framework.
	void setLayer(int newLayer);
	void setLocation(sf::Vector2f newLocation);
	void setScale(sf::Vector2f newScale);
	void setRotation(float newRotation);
	void setTransform(Transform newTransform);

	//Call this to read the transform.
	Transform getTransform();

	void addNode(SceneNode* node, sf::Vector2f location);

	SceneNode();
	~SceneNode(void);

protected:
	std::vector<SceneNode*> children;

private:
	Transform transform;
	SceneNode* parent;

};
