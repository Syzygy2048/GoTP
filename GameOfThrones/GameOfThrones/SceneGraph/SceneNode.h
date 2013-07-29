#ifndef _SCENENODE_
#define _SCENENODE_

#include <vector>
#include <glm\glm.hpp>
#include "..\InputHandler.h"

class SceneNode
{
public:
	
	
	virtual void update(double dT, InputHandler* input);
	virtual void draw(double dT, glm::mat4 vp);


	void addNode(SceneNode* node);

	static enum NodeType
	{
		ROOT = 0x100,
		TRANSLATE = 0x101,
		MESH = 0x102,
		LIGHT = 0x103,
		CAMERA = 0x104
	};

	SceneNode();
	SceneNode(NodeType type);
	~SceneNode(void);
protected:
	std::vector<SceneNode*> childs;
private:
	
	const NodeType type;
	SceneNode* parent;

	
};

#endif