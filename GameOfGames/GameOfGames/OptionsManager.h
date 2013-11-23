#pragma once

#include <string>
#include <SFML\Graphics.hpp>

enum WideScreenMode {NOTSET=-1, NOWIDE = 0, SIXTEENBYNINE = 1, SIXTEENBYTEN = 2};

class OptionsManager
{
public:

	sf::Vector2f getInternalResolution(){ return *internalResolution; }

	void setDisplayResolution(sf::Vector2f* newDisplayResolution);
	sf::Vector2f getDisplayResolution(){ return *displayResolution; }

	void setWideScreenMode(WideScreenMode newWideScreenMode);
	WideScreenMode getWidescreenMode();

	sf::Vector2f* getFinalScreenRatio();
	sf::Vector2f* getCachedScreenRatio();

	int getFullscreen(){ return fullscreen; }
	void setFullScreen(int newFullScreen);

	int getVSync(){ return vSync; }
	void setVsyncEnabled(int enabled);

	int getShowFps(){return showFps;}
	void setShowFps(bool newShowFps);

	bool getOptionsChanged(){return optionsChanged;}
	void informWindowReloaded(){optionsChanged = false;}
	

	static OptionsManager* getInstance();
	~OptionsManager(void);

	void setWindowInstance(sf::Window* newWindow){ windowPointer = newWindow;}

private:
	sf::Window* windowPointer;
	OptionsManager* instance;
	OptionsManager(void);									//private because singleton
	OptionsManager(const OptionsManager&);					//prevents copy constructor
	OptionsManager& operator = (const OptionsManager&);		//some reason I dont know why


	/* Writes missing default values into the settings file (created if missing) and memory. Called from constructor. */
	void writeMissingDefault();

	/* Set's all the values to their default values. Changes need to be applied via writeChanged() to take effect. */
	void setDefault();

	/* Writes all changed values into the settings file and memory. */
	void writeChangedSettings();

	/* Reads all values from a setting file into memory. Called from the constructor. */
	void read();

	bool optionsChanged;

	sf::Vector2f* internalResolution;
	sf::Vector2f* displayResolution;
	int fullscreen;
	int showFps;
	int vSync;
	int wideScreen;

	sf::Vector2f* defaultInternalResolution;
	sf::Vector2f* defaultDisplayResolution;
	int defaultFullscreen;
	int defaultVSync;
	int defaultWideScreen;
	int defaultShowFps;

	sf::Vector2f* cachedScreenRatio;
	std::string* path;
};

