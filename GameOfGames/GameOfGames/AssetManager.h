#pragma once
#include <vector>
#include <SFML/Graphics.hpp>

class AssetManager
{
public:
	static sf::Texture* getTexture(std::string textureName);
	static void unsubscribeToTexture(sf::Texture* texture);

private:
	struct TextureData
	{
		sf::Texture* texture;
		std::string* textureName;
		int usersAmount;
	};
};