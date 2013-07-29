#include "SceneNode.h"

SceneNode::SceneNode() : type(ROOT)
{
	parent = NULL;
}

SceneNode::SceneNode(NodeType type) : type(type)
{
	parent = NULL;
}


void SceneNode::update(double dT, InputHandler* input)
{
	for(SceneNode* n : childs)
	{
		n->update(dT, input);
	}
}

void SceneNode::draw(double dT, glm::mat4 vp)
{
	for(SceneNode* n : childs)
	{
		n->draw(dT, vp);
	}
}

void SceneNode::addNode(SceneNode* node)
{
	node->parent = this;
	childs.push_back(node);
}

SceneNode::~SceneNode(void)
{
	for(SceneNode* child : childs)
	{
		delete child;
	}
}
