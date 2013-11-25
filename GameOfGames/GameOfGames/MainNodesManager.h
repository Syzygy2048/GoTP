#pragma once
#include "Enums.h"

class SceneNode;

class MainNodesManager
{
public:
	static MainNodesManager* getInstance();

	void setRootNode(SceneNode* node, RootNodeType type);
	SceneNode* getRootNode(RootNodeType type);

private:
	MainNodesManager(void);										
	MainNodesManager(const MainNodesManager&);					
	MainNodesManager& operator = (const MainNodesManager&);

	MainNodesManager* instance;
	SceneNode* scenarioNode;
	SceneNode* HUDNode;
	SceneNode* backgroundNode;
};