#include "SceneNode.h"

SceneNode::SceneNode()
{
	parent = NULL;

	Scale newScale;

	newScale.X = 1;
	newScale.Y = 1;
}

void SceneNode::tick(float deltaTime)
{
	for(SceneNode* node : childs)
	{
		node->tick(deltaTime);
	}
}

void SceneNode::draw(float deltaTime, sf::RenderWindow* target)
{
	for(SceneNode* node : childs)
	{
		node->draw(deltaTime,target);
	}
}

void SceneNode::addNode(SceneNode* node)
{
	node->parent = this;
	childs.push_back(node);
}

SceneNode::~SceneNode(void)
{
	for(SceneNode* node : childs)
	{
		delete node;
	}
}
