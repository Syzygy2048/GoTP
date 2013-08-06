#pragma once
#include <vector>
#include <SFML/Graphics.hpp>

class UIView;

class AssetManager
{
public:
	//avoid calling these, sprite classes already know how to handle subscriptions/unsubscriptions
	 sf::Texture* getTexture(std::string textureName);
	 void unsubscribeToTexture(sf::Texture* unsubscribing);

	 void clearClickables();
	 void addDrawnClickable(UIView* toAdd);
	 void checkOnClickables();

	 static AssetManager* getInstance();

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

	std::vector<UIView*>* drawnClickables;
	std::vector<TextureData*>* texturesData;
};