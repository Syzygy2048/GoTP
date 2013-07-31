#include "SceneNode.h"

SceneNode::SceneNode()
{
	parent = NULL;

	transform.scale = sf::Vector2f(1.f,1.f);
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
		node->draw(deltaTime,target);
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
	transform.layer = newLayer;

	transformUpdated();
}

void SceneNode::setLocation(sf::Vector2f newLocation)
{
	transform.location = newLocation;

	transformUpdated();
}

void SceneNode::setScale(sf::Vector2f newScale)
{
	transform.scale = newScale;

	transformUpdated();
}

void SceneNode::setRotation(float newRotation)
{
	transform.rotation = newRotation;

	transformUpdated();
} 

void SceneNode::setTransform(SceneNode::Transform newTransform)
{
	transform = newTransform;

	transformUpdated();
}

SceneNode::Transform SceneNode::getTransform()
{
	return transform;
}

sf::Vector2f SceneNode::getWorldLocation()
{
	if(parent)
	{
		return parent->getWorldLocation()+transform.location;
	}
	else
	{
		return transform.location;
	}
}

float SceneNode::getTotalRotation()
{
	if (parent)
	{
		return parent->getTotalRotation()+transform.rotation;
	}
	else
	{
		return transform.rotation;
	}
}

sf::Vector2f SceneNode::getTotalScale()
{
	if(parent)
	{
		return sf::Vector2f(parent->getTotalScale().x*transform.scale.x,parent->getTotalScale().y*transform.scale.y);
	}
	else
	{
		return transform.scale;
	}
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
