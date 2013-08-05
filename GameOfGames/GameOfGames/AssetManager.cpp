#include "AssetManager.h"
#include <iostream>

void AssetManager::unsubscribeToTexture(sf::Texture* texture)
{
	for(unsigned int i = 0; i < texturesData->size();i++)
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

sf::Texture* AssetManager::getTexture(std::string textureName)
{
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
		toAdd->texture->setSmooth(true);

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

void AssetManager::clearClickables()
{
	if (drawnClickables)
	{
		while (!drawnClickables->empty())
		{
			drawnClickables->pop_back();
		}
	}
}

void AssetManager::addDrawnClickable(UIView* toAdd)
{
	drawnClickables->push_back(toAdd);
}

AssetManager::AssetManager()
{
	texturesData = new std::vector<TextureData*>();
	drawnClickables = new std::vector<UIView*>();
}

AssetManager* AssetManager::getIntance()
{
	static AssetManager* instance;

	if (!instance)
	{
		instance = new AssetManager();
	}

	return instance;
}
