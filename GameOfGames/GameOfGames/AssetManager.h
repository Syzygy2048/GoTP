#pragma once
#include <vector>
#include <SFML/Graphics.hpp>

class AssetManager
{
public:
	static AssetManager* getInstance();

	//Sprite classes already know how to handle subscriptions/unsubscriptions, dont call these.
	 sf::Texture* subscribeToTexture(std::string textureName);
	 void unsubscribeToTexture(sf::Texture* unsubscribing);

private:
	AssetManager(void);										
	AssetManager(const AssetManager&);					
	AssetManager& operator = (const AssetManager&);

	struct TextureData
	{
		sf::Texture* texture;
		std::string* textureName;
		int usersAmount;
	};

	std::vector<TextureData*>* texturesData;
};