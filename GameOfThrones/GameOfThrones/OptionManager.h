#pragma once

#include <string>
//Handles 
class OptionManager
{
public:

	int getResolutionX(){ return resolutionX; }
	int getResolutionY(){ return resolutionY; }
	bool getFullscreen(){ return fullscreen; }
	bool getVSync(){ return vSync; }

	OptionManager(void);
	~OptionManager(void);

private:
	/* Writes missing default values into the settings file (created if missing) and memory. Called from constructor. */
	void writeMissingDefault();

	/* Set's all the values to their default values. Changes need to be applied via writeChanged() to take effect. */
	void setDefault();

	/* Writes all changed values into the settings file and memory. */
	void writeChanged();

	/* Reads all values from a setting file into memory. Called from the constructor. */
	void read();

	int resolutionX;
	int resolutionY;
	bool fullscreen;
	bool vSync;

	int changedResolutionX;
	int changedResolutionY;
	bool changedFullscreen;
	bool changedVSync;

	int defaultResolutionX;
	int defaultResolutionY;
	bool defaultFullscreen;
	bool defaultVSync;

	std::string path;
};

