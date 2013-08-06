#include "SceneNode.h"

SceneNode::SceneNode()
{
	parent = NULL;
	cachedLocation = new sf::Vector2f(0.f,0.f);
	cachedScale = new sf::Vector2f(1.f,1.f);
	children = new std::vector<SceneNode*>();
	transform = new sf::Transform();
	hidden = false;
}

void SceneNode::setHidden(bool newHidden)
{
	hidden = newHidden;
}

void SceneNode::destroy()
{
	if (parent)
	{
		parent->eraseNode(this);
	}
	else
	{
		delete this;
	}
}

void SceneNode::tick(float deltaTime)
{
	for(SceneNode* node : *children)
	{
		node->tick(deltaTime);
	}
}

void SceneNode::draw(float deltaTime, sf::RenderWindow* target, sf::Transform parentTranform)
{
	if(!isHidden())
	{
		sf::Transform totalTransform = parentTranform**transform;

		onDraw(deltaTime,target,totalTransform);

		for(SceneNode* node : *children)
		{
			node->draw(deltaTime,target, totalTransform);
		}
	}


}

void SceneNode::setLayer(int newLayer)
{
	layer = newLayer;

	if(parent)
	{
		parent->adjustLayerFor(this);
	}
}

void SceneNode::adjustLayerFor(SceneNode* node)
{
	//we just remove from the list and readd it in the right place
	for (unsigned int i = 0; i < children->size();i++)
	{
		if (children->at(i)==node)
		{
			children->erase(children->begin()+i);
		}
	}

	finalChildInsertion(node);
}

bool SceneNode::detachNode(SceneNode* toRemove)
{
	for(unsigned int i = 0; i < children->size();i++)
	{
		SceneNode* node = children->at(i);

		if(node == toRemove)
		{
			toRemove->parent = NULL;

			children->erase(children->begin()+i);

			return true;
		}
	}

	return false;
}

bool SceneNode::eraseNode(SceneNode* toRemove)
{
	bool response = detachNode(toRemove);

	if (response)
	{
		delete toRemove;
	}

	return response;		
}

SceneNode* SceneNode::nodeAt(unsigned int index)
{
	if (index < children->size())
	{
		return children->at(index);
	}
	else
	{
		return NULL;
	}
}

void SceneNode::setLocation(sf::Vector2f newLocation)
{
	move(sf::Vector2f(newLocation.x - cachedLocation->x,newLocation.y - cachedLocation->y));
}

void SceneNode::move(sf::Vector2f newLocation)
{
	//undo rotation and scale before moving if we have a parent
	//this way children rotate in place
	//but root nodes should move according to previous scale, because their scale is the screen ratio
	if(parent)
	{
		transform->rotate(-cachedRotation);
		transform->scale(1.f/cachedScale->x,1.f/cachedScale->y);
	}

	cachedLocation->x+=newLocation.x;
	cachedLocation->y+=newLocation.y;

	transform->translate(newLocation);

	if(parent)
	{
		transform->scale(*cachedScale);
		transform->rotate(cachedRotation);
	}
}

void SceneNode::setScale(sf::Vector2f newScale)
{
	//undo previous scale because the method is "setScale" and not just "scale"
	transform->scale(1.f/cachedScale->x,1.f/cachedScale->y);

	cachedScale->x = newScale.x;
	cachedScale->y = newScale.y;

	transform->scale(newScale);
}

void SceneNode::setRotation(float newRotation)
{
	//see setScale
	transform->rotate(-cachedRotation);

	cachedRotation = newRotation;

	transform->rotate(newRotation);
} 

void SceneNode::setTransform(sf::Transform* newTransform)
{
	transform = newTransform;
}

bool SceneNode::addNode(SceneNode* node, sf::Vector2f location)
{
	if(node->parent)
	{
		return false;
	}

	node->parent = this;

	node->move(location);

	finalChildInsertion(node);

	return true;
}

void SceneNode::finalChildInsertion(SceneNode* node)
{
	//made this method so I could use it both for addNode and adjust layer
	bool added = false;

	if (children->empty())
	{
		children->push_back(node);

		return;
	}

	for (unsigned int i = 0; i < children->size();i++)
	{
		SceneNode* child = children->at(i);

		if (node->getLayer() > child->getLayer())
		{
			children->insert(children->begin()+i,node);

			added = true;

			break;
		}
	}

	if (!added)
	{
		children->push_back(node);
	}
}

SceneNode::~SceneNode(void)
{
	for(SceneNode* node : *children)
	{
		delete node;
	}

	delete cachedScale;
	delete transform;
	delete cachedLocation;
}
