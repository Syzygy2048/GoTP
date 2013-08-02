#pragma once

#include <string>
#include <SFML/Graphics.hpp>
//Handles 
class OptionsManager
{
public:

	sf::Vector2i getInternalResolution(){ return internalResolution; };
	sf::Vector2i getDisplayResolution(){ return displayResolution; };
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

	sf::Vector2i internalResolution;
	sf::Vector2i displayResolution;
	int fullscreen;
	int vSync;

	sf::Vector2i defaultInternalResolution;
	sf::Vector2i defaultDisplayResolution;
	int defaultFullscreen;
	int defaultVSync;

	std::string path;
};

