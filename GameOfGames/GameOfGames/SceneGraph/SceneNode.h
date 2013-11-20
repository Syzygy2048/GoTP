#pragma once

#include <vector>
#include <iostream>
#include <SFML\Graphics.hpp>

class SceneNode
{
public:
	void draw(float deltaTime, sf::RenderWindow* target, sf::Transform parentTranform);

	//Override and dont forget to call the parent implementation.
	virtual void tick(float deltaTtime);
	virtual void onDraw(float deltaTime, sf::RenderWindow* target, sf::Transform parentTranform){}
	
	//settings
	void setHidden(bool newHidden);
	bool isHidden(){ return hidden; }
	void setLocation(sf::Vector2f newLocation);
	int getLayer() { return layer; }
	void setLayer(int newLayer);
	void move(sf::Vector2f newLocation);
	void setScale(sf::Vector2f newScale);
	void setRotation(float newRotation);
	void setTransform(sf::Transform* newTransform);
	float getCachedRotation() { return cachedRotation; }
	
	//children operations
	//call destroy instead of delete manually, it will perform actions on its parent.
	void destroy();
	SceneNode* nodeAt(unsigned int index);
	bool addNode(SceneNode* node, sf::Vector2f location);
	bool detachNode(SceneNode* toRemove);
	bool eraseNode(SceneNode* toRemove);

	//constructors/destructors
	SceneNode();
	~SceneNode(void);

	//locked readers
	const sf::Transform getTransform(){ return *transform; }
	const SceneNode* getParent() { return parent; }
	const std::vector<SceneNode*>* getChildren() { return children; }
	const sf::Vector2f* getCachedLocation() { return cachedLocation; }
	const sf::Vector2f* getCachedScale() { return cachedScale; }

private:
	SceneNode* parent;
	std::vector<SceneNode*>* children;
	sf::Vector2f* cachedLocation;
	sf::Vector2f* cachedScale;
	float cachedRotation;
	int layer;
	void adjustLayerFor(SceneNode* child);
	void finalChildInsertion(SceneNode* node);
	sf::Transform* transform;
	bool hidden;
};
