#pragma once
#include <vector>
#include <SFML/Graphics.hpp>

class AssetManager
{
public:
	static sf::Texture* getTexture(std::string textureName,sf::Texture* unsubscribing);

private:
	struct TextureData
	{
		sf::Texture* texture;
		std::string* textureName;
		int usersAmount;
	};
};