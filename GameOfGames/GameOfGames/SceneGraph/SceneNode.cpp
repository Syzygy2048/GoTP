#include "SceneNode.h"

SceneNode::SceneNode()
{
	parent = NULL;

	cachedLocation = new sf::Vector2f(0.f,0.f);
	cachedScale = new sf::Vector2f(1.f,1.f);

	children = new std::vector<SceneNode*>();

	transform = new sf::Transform();
}

void SceneNode::tick(float deltaTime)
{
	for(SceneNode* node : *children)
	{
		node->tick(deltaTime);
	}
}

void SceneNode::draw(float deltaTime, sf::RenderWindow* target)
{
	for(SceneNode* node : *children)
	{
		sf::Transform totalTransform = *transform;
		node->onDraw(deltaTime,target,totalTransform*node->getTransform());
		node->draw(deltaTime,target, totalTransform);
	}
}

void SceneNode::draw(float deltaTime, sf::RenderWindow* target, sf::Transform parentTranform)
{
	for(SceneNode* node : *children)
	{
		sf::Transform totalTransform = parentTranform**transform;
		node->onDraw(deltaTime,target,totalTransform*node->getTransform());
		node->draw(deltaTime,target, totalTransform);
	}
}

void SceneNode::onDraw(float deltaTime, sf::RenderWindow* target,  sf::Transform parentTranform)
{
}

void SceneNode::setScreenRatio(sf::Vector2f* newRatio)
{
	screenRatio = newRatio;
}

void SceneNode::setLayer(int newLayer)
{
	//transform.layer = newLayer;
}

void SceneNode::setLocation(sf::Vector2f newLocation)
{
	move(sf::Vector2f(newLocation.x-cachedLocation->x,newLocation.y-cachedLocation->y));
}

void SceneNode::move(sf::Vector2f newLocation)
{
	transform->rotate(-cachedRotation);
	transform->scale(1.f/cachedScale->x,1.f/cachedScale->y);
	
	cachedLocation->x+=newLocation.x;
	cachedLocation->y+=newLocation.y;

	transform->translate(newLocation);

	transform->scale(*cachedScale);
	transform->rotate(cachedRotation);
}

void SceneNode::scale(sf::Vector2f newScale)
{
	sf::Vector2f* temp = new sf::Vector2f(newScale.x*cachedScale->x,newScale.y*cachedScale->y);

	delete cachedScale;

	cachedScale = temp;

	transform->scale(newScale);
}

void SceneNode::setScale(sf::Vector2f newScale)
{
	transform->scale(1.f/cachedScale->x,1.f/cachedScale->y);

	cachedScale->x = newScale.x;
	cachedScale->y = newScale.y;

	transform->scale(newScale);
}

void SceneNode::setRotation(float newRotation)
{
	transform->rotate(-cachedRotation);

	cachedRotation = newRotation;

	transform->rotate(newRotation);
} 

void SceneNode::setTransform(sf::Transform* newTransform)
{
	transform = newTransform;
}

sf::Transform SceneNode::getTransform()
{
	return *transform;
}

void SceneNode::addNode(SceneNode* node, sf::Vector2f location)
{
	node->parent = this;
	node->setScreenRatio(screenRatio);
	node->setLocation(location);
	children->push_back(node);
}

SceneNode::~SceneNode(void)
{
	for(SceneNode* node : *children)
	{
		delete node;
	}

	delete cachedLocation;
}
