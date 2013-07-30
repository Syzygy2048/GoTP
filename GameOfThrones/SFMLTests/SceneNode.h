#pragma once
#include <vector>
#include <iostream>
#include <SFML/Graphics.hpp>

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

	virtual void tick(float deltaTtime);
	virtual void initSprite();
	void superDraw(float deltaTtime, sf::RenderWindow* target);
	virtual void draw(float deltaTime, sf::RenderWindow* target);

	void setTransform(Transform newTransform);
	void setLocation(Location newLocation);
	void setScale(Scale newScale);
	void setLayer(int newLayer);
	void setRotation(float newRotation);

	SceneNode();

	void addNode(SceneNode* node);

	~SceneNode(void);
protected:
	std::vector<SceneNode*> childs;

private:
	Transform transform;
	SceneNode* parent;

};
