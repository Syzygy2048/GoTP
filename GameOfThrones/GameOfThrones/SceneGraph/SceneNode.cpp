#include "SceneNode.h"

SceneNode::SceneNode() : type(ROOT)
{
	parent = NULL;
}

SceneNode::SceneNode(NodeType type) : type(type)
{
	parent = NULL;
}

void SceneNode::tick(double dT)
{
	for(SceneNode* node : childs)
	{
		node->tick(dT);
	}
}

void SceneNode::draw(double dT)
{
	for(SceneNode* node : childs)
	{
		node->draw(dT);
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
