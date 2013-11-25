#include "MainNodesManager.h"

MainNodesManager* MainNodesManager::getInstance()
{
	static MainNodesManager* instance;

	if (!instance)
	{
		instance = new MainNodesManager();
	}

	return instance;
}

MainNodesManager::MainNodesManager()
{
}

void MainNodesManager::setRootNode(SceneNode* node, RootNodeType type)
{
	switch (type)
	{
	case BACKGROUND:
		backgroundNode = node;
		break;
	case SCENARIO:
		scenarioNode = node;
		break;
	case HUD:
		HUDNode = node;
		break;
	}
}

SceneNode* MainNodesManager::getRootNode(RootNodeType type)
{
	switch (type)
	{
	case BACKGROUND:
		return backgroundNode;
	case SCENARIO:
		return scenarioNode;
	case HUD:
		return HUDNode;
	default:
		return nullptr;
	}
}