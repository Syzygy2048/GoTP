#pragma once

#include <string>
#include <SFML\Graphics.hpp>
#include "Enums.h"

class OptionsManager
{
public:
	static OptionsManager* getInstance();
	~OptionsManager(void);

	sf::Vector2f getInternalResolution(){ return *internalResolution; }

	void setDisplayResolution(sf::Vector2f* newDisplayResolution);
	sf::Vector2f getDisplayResolution(){ return *displayResolution; }

	void setWideScreenMode(WideScreenMode newWideScreenMode);
	WideScreenMode getWidescreenMode();

	//Final screen ratio should be used on the root nodes, just that.
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
	
	void setWindowInstance(sf::Window* newWindow){ windowPointer = newWindow;}

private:
	OptionsManager(void);									
	OptionsManager(const OptionsManager&);				
	OptionsManager& operator = (const OptionsManager&);	
		
	void writeMissingDefault();
	void setDefault();
	void writeChangedSettings();
	void read();

	OptionsManager* instance;
	sf::Vector2f* cachedScreenRatio;
	std::string* path;
	sf::Window* windowPointer;
	sf::Vector2f* internalResolution;
	sf::Vector2f* displayResolution;
	sf::Vector2f* defaultInternalResolution;
	sf::Vector2f* defaultDisplayResolution;

	bool optionsChanged;
	int fullscreen;
	int showFps;
	int vSync;
	int wideScreen;
	int defaultFullscreen;
	int defaultVSync;
	int defaultWideScreen;
	int defaultShowFps;
};

