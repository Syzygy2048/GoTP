#pragma once

#include <string>
#include <SFML/Graphics.hpp>
//Handles 
class OptionsManager
{
public:

	sf::Vector2f getInternalResolution(){ return *internalResolution; };
	sf::Vector2f getDisplayResolution(){ return *displayResolution; };
	sf::Vector2f* getFinalScreenRatio();
	sf::Vector2f* getCachedScreenRatio();
	int getFullscreen(){ return fullscreen; }
	int getVSync(){ return vSync; }

	OptionsManager(void);
	~OptionsManager(void);

private:
	/* Writes missing default values into the settings file (created if missing) and memory. Called from constructor. */
	void writeMissingDefault();

	/* Set's all the values to their default values. Changes need to be applied via writeChanged() to take effect. */
	void setDefault();

	/* Writes all changed values into the settings file and memory. */
	void writeChanged();

	/* Reads all values from a setting file into memory. Called from the constructor. */
	void read();

	sf::Vector2f* internalResolution;
	sf::Vector2f* displayResolution;
	int fullscreen;
	int vSync;
	int wideScreen;

	sf::Vector2f* defaultInternalResolution;
	sf::Vector2f* defaultDisplayResolution;
	int defaultFullscreen;
	int defaultVSync;
	int defaultWideScreen;

	sf::Vector2f* cachedScreenRatio;
	std::string* path;
};

