#include "OptionsManager.h"
#include <fstream>
#include <string>
#include <iostream>
#include <sys/stat.h>


OptionsManager::OptionsManager() : path(new std::string ("settings.txt")),defaultDisplayResolution(new sf::Vector2f(1920.f, 1080.f)), defaultInternalResolution(new sf::Vector2f(720.f,720.f)), defaultFullscreen(1), defaultWideScreen(1),defaultVSync(1)
{
	fullscreen = -1;
	vSync = -1;
	wideScreen = -1;

	internalResolution = new sf::Vector2f();
	displayResolution = new sf::Vector2f();

	read();

	if(internalResolution->x == 0 || 
		internalResolution->y == 0 || 
		displayResolution->x == 0 || 
		displayResolution->y == 0 ||
		fullscreen == -1 || 
		wideScreen == -1 ||
		vSync == -1)
	{
		writeMissingDefault();
	}
}

sf::Vector2f* OptionsManager::getCachedScreenRatio()
{
	if(!cachedScreenRatio)
	{
		return getFinalScreenRatio();
	}
	else
	{
		return cachedScreenRatio;
	}
}
//screen ratio should be used on the root nodes, just that, see main.
sf::Vector2f* OptionsManager::getFinalScreenRatio()
{
	if(cachedScreenRatio)
	{
		delete cachedScreenRatio;
	}

	float temp = 1.f;

	switch (wideScreen)
	{
	case 0:
		temp = 4.f/3.f;
		break;
	case 1:
		temp = 16.f/9.f;
		break;

	case 2:
		temp = 16.f/10.f;
		break;
	}

	internalResolution->x *= temp;

	cachedScreenRatio = new sf::Vector2f(displayResolution->x/internalResolution->x, displayResolution->y/internalResolution->y);

	return cachedScreenRatio;
}

void OptionsManager::read()
{

	std::ifstream fs;
	fs.open(path->c_str(), std::ios::in);
	if(!fs.is_open())
	{
		std::cerr << "couldn't open filestream" << std::endl;
		return;
	}

	std::string line;

	//read line, check which setting it is and interpret it's value
	while (std::getline(fs, line, '='))
	{
		if(line.find("x internalResolution") != std::string::npos)
		{
			std::getline(fs, line);
			internalResolution->x = std::stof(line);
		}
		else if(line.find("y internalResolution") != std::string::npos)
		{
			std::getline(fs, line);
			internalResolution->y = std::stof(line);
		}
		else if(line.find("x resolution") != std::string::npos)
		{
			std::getline(fs, line);
			displayResolution->x = std::stof(line);
		} 
		else if(line.find("y resolution") != std::string::npos)
		{
			std::getline(fs, line);
			displayResolution->y = std::stof(line);
		}
		else if(line.find("fullscreen") != std::string::npos)
		{
			std::getline(fs, line);
			fullscreen = std::stoi(line);
		}
		else if(line.find("vsync") != std::string::npos)
		{
			std::getline(fs, line);
			vSync = std::stoi(line);
		}
		else if(line.find("wide") != std::string::npos)
		{
			std::getline(fs, line);
			wideScreen = std::stoi(line);
		}
	}

	fs.close();
}

void OptionsManager::writeMissingDefault()
{
	std::ofstream fs;
	fs.open(path->c_str(), std::ios::out | std::ios::app);
	if(fs.is_open())
	{
		if(internalResolution->x == 0)
		{
			internalResolution->x = defaultInternalResolution->x;
			fs << "x internalResolution = " << internalResolution->x << std::endl;
		}

		if(internalResolution->y == 0)
		{
			internalResolution->y = defaultInternalResolution->y;
			fs << "y internalResolution = " << internalResolution->y << std::endl;
		}

		if(displayResolution->x == 0)
		{
			displayResolution->x = defaultDisplayResolution->x;
			fs << "x resolution = " << displayResolution->x << std::endl;
		}

		if(displayResolution->y == 0)
		{
			displayResolution->y = defaultDisplayResolution->y; 
			fs << "y resolution = " << displayResolution->y << std::endl;
		}

		if(fullscreen == -1)
		{
			fullscreen = defaultFullscreen;
			fs << "fullscreen = " << defaultFullscreen << std::endl;
		}

		if(vSync == -1)
		{
			vSync = defaultVSync;
			fs << "vsync = " << defaultVSync << std::endl;
		}

		if (wideScreen == -1)
		{
			wideScreen = defaultWideScreen;
			fs << "wide = " << defaultWideScreen << std::endl;
		}

		fs.close();
	}
}

void OptionsManager::setDefault()
{
	displayResolution = defaultDisplayResolution;
	internalResolution = defaultInternalResolution;
	fullscreen = defaultFullscreen;
	vSync = defaultVSync;
	wideScreen = defaultWideScreen;

	writeChanged();
}

void OptionsManager::writeChanged()
{
	std::ofstream fs;

	fs.open(*path, std::ios::out | std::ios::trunc);

	if(fs.is_open())
	{
		fs << "x internalResolution = " << internalResolution->x << std::endl;

		fs << "y internalResolution = " << internalResolution->y << std::endl;

		fs << "x resolution = " << displayResolution->x << std::endl;

		fs << "y resolution = " << displayResolution->y << std::endl;

		fs << "fullscreen = " << fullscreen << std::endl;

		fs << "vsync = " << vSync << std::endl;

		fs << "wide = "<<wideScreen << std::endl;

		fs.close();
	}
}

OptionsManager::~OptionsManager(void)
{
	delete internalResolution;
	delete displayResolution;

	delete cachedScreenRatio;
	delete path;
	delete defaultInternalResolution;
	delete defaultDisplayResolution;

}
