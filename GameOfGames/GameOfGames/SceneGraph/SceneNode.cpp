#include "SceneNode.h"

SceneNode::SceneNode()
{
	parent = NULL;
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
		node->draw(deltaTime,target, transform);
	}
}

void SceneNode::draw(float deltaTime, sf::RenderWindow* target, sf::Transform parentTranform)
{
	for(SceneNode* node : children)
	{
		node->draw(deltaTime,target, transform*parentTranform);
	}
}

void SceneNode::transformUpdated()
{
	for each (SceneNode* child in children)
	{
		child->transformUpdated();
	}
}

void SceneNode::setLayer(int newLayer)
{
	//transform.layer = newLayer;

	transformUpdated();
}

void SceneNode::setLocation(sf::Vector2f newLocation)
{
	transform.translate(newLocation);

	transformUpdated();
}

void SceneNode::setScale(sf::Vector2f newScale)
{
	transform.scale(newScale);

	transformUpdated();
}

void SceneNode::setRotation(float newRotation)
{
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
