#ifndef _SCENENODE_
#define _SCENENODE_

#include <vector>
#include <glm\glm.hpp>
#include "..\InputHandler.h"

class SceneNode
{
public:
	struct Location
	{
		float X;
		float Y;
	};

	struct Scale
	{
		float X;
		float Y;
	};

	struct Transform
	{
		float rotation;
		int layer;
		Location location;
		Scale scale;
	};

	virtual void tick(double deltaTtime);
	virtual void draw(double deltaTtime);

	
	void setTransform(Transform newTransform);
	void setLocation(Location newLocation);
	void setScale(Scale newScale);
	void setLayer(int newLayer);
	void setRotation(float newRotation);
	
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