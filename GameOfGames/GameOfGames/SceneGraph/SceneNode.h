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

	void setScreenRatio(sf::Vector2f* newRatio);

	void setLayer(int newLayer);
	void move(sf::Vector2f newLocation);
	void setScale(sf::Vector2f newScale);
	void setRotation(float newRotation);
	void setTransform(sf::Transform* newTransform);

	//Call this to read the transform.
	sf::Transform getTransform();

	void addNode(SceneNode* node, sf::Vector2f location);

	SceneNode();
	~SceneNode(void);

protected:
	SceneNode* parent;
	std::vector<SceneNode*>* children;
	sf::Vector2f* cachedLocation;
	sf::Vector2f* cachedScale;

private:
	float cachedRotation;
	sf::Transform* transform;
};
