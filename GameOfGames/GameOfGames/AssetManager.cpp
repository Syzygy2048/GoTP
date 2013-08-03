#include "AssetManager.h"
#include <iostream>

sf::Texture* AssetManager::getTexture(std::string textureName)
{
	static std::vector<TextureData*>* texturesData;

	if (!texturesData)
	{
		texturesData = new std::vector<TextureData*>();
	}

	for each (TextureData* data in *texturesData)
	{
		if (!textureName.compare(*data->textureName))
		{
			data->usersAmount++;

			return data->texture;
		}
	}

	TextureData* toAdd = new TextureData();

	toAdd->textureName =  new std::string(textureName);
	toAdd->usersAmount = 1;
	toAdd->texture = new sf::Texture();

	std::string path = std::string("Assets\\Sprites\\");

	path.append(textureName);

	if (toAdd->texture->loadFromFile(path))
	{
		texturesData->push_back(toAdd);

		return toAdd->texture;
	}
	else
	{
		delete toAdd->textureName;
		delete toAdd->texture;

		delete toAdd;

		return NULL;
	}
}

 void  AssetManager::unsubscribeToTexture(sf::Texture* texture)
{
	static std::vector<TextureData*>* texturesData;

	if(!texturesData)
	{
		return;
	}

	for(int i = 0; i < texturesData->size();i++)
	{
		TextureData* data = texturesData->at(i);

		if (texture == data->texture)
		{
			data->usersAmount--;

			if (!data->usersAmount)
			{
				texturesData->erase(texturesData->begin()+i);

				delete data->texture;

				delete data->textureName;

				delete data;
			}
		}
	}
}