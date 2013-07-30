#include "TestChar.h"

TestChar::TestChar()
{
	if (texture.loadFromFile("caipira.png"))
	{
		texture.setSmooth(true);

		sprite.setTexture(texture);
	}
}

void TestChar::draw(float deltaTime, sf::RenderWindow* target)
{
	target->draw(sprite);

	SceneNode::draw(deltaTime, target);
}
