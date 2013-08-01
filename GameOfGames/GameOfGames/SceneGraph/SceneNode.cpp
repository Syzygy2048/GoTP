#include "SceneNode.h"

SceneNode::SceneNode()
{
	parent = NULL;

	cachedScale = sf::Vector2f(1.f,1.f);
}

void SceneNode::tick(float deltaTime)
{
	for(SceneNode* node : children)
	{
		node->tick(deltaTime);
	}
}

void SceneNode::draw(float deltaTime, sf::RenderWindow* target)
{
	for(SceneNode* node : children)
	{
		sf::Transform totalTransform = transform;
		node->onDraw(deltaTime,target,totalTransform*node->getTransform());
		node->draw(deltaTime,target, totalTransform);
	}
}

void SceneNode::draw(float deltaTime, sf::RenderWindow* target, sf::Transform parentTranform)
{
	for(SceneNode* node : children)
	{
		sf::Transform totalTransform = parentTranform*transform;
		node->onDraw(deltaTime,target,totalTransform*node->getTransform());
		node->draw(deltaTime,target, totalTransform);
	}
}

void SceneNode::onDraw(float deltaTime, sf::RenderWindow* target,  sf::Transform parentTranform)
{
}

void SceneNode::transformUpdated()
{
	/*for each (SceneNode* child in children)
	{
		child->transformUpdated();
	}*/
}

void SceneNode::setLayer(int newLayer)
{
	//transform.layer = newLayer;

	transformUpdated();
}

void SceneNode::setLocation(sf::Vector2f newLocation)
{
	transform.rotate(-cachedRotation);
	transform.scale(1.f/cachedScale.x,1.f/cachedScale.y);
	
	//transform.translate(-cachedLocation);

	//cachedLocation=newLocation;

	transform.translate(newLocation);

	transform.scale(cachedScale);
	transform.rotate(cachedRotation);
	
	transformUpdated();
}

void SceneNode::setScale(sf::Vector2f newScale)
{
	cachedScale = sf::Vector2f(newScale.x*cachedScale.x,newScale.y*cachedScale.y);

	transform.scale(newScale);
	
	transformUpdated();
}

void SceneNode::setRotation(float newRotation)
{
	transform.rotate(-cachedRotation);

	cachedRotation = newRotation;

	transform.rotate(newRotation);

	transformUpdated();
} 

void SceneNode::setTransform(sf::Transform newTransform)
{
	transform = newTransform;

	transformUpdated();
}

sf::Transform SceneNode::getTransform()
{
	return transform;
}

void SceneNode::addNode(SceneNode* node, sf::Vector2f location)
{
	node->parent = this;
	node->setLocation(location);
	children.push_back(node);
}

SceneNode::~SceneNode(void)
{
	for(SceneNode* node : children)
	{
		delete node;
	}
}
