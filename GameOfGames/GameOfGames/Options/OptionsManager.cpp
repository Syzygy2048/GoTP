#include "OptionsManager.h"
#include <fstream>
#include <string>
#include <iostream>
#include <sys/stat.h>

OptionsManager::OptionsManager() : path("settings.txt"),defaultDisplayResolution(sf::Vector2i(720,720)), defaultInternalResolution(sf::Vector2i(720,720)), defaultFullscreen(0), defaultVSync(0)
{
	fullscreen = -1;
	vSync = -1;

	read();

	if(internalResolution.x == 0 || 
		internalResolution.y == 0 || 
		displayResolution.x == 0 || 
		displayResolution.y == 0 ||
		fullscreen == -1 || 
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

sf::Vector2f* OptionsManager::getFinalScreenRatio()
{
	if(cachedScreenRatio)
	{
		delete cachedScreenRatio;
	}

	cachedScreenRatio = new sf::Vector2f(displayResolution.x/internalResolution.x, displayResolution.y/internalResolution.y);

	return cachedScreenRatio;
}

void OptionsManager::read()
{

	std::ifstream fs;
	fs.open(path.c_str(), std::ios::in);
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
			internalResolution.x = std::stoi(line);
		}
		else if(line.find("y internalResolution") != std::string::npos)
		{
			std::getline(fs, line);
			internalResolution.y = std::stoi(line);
		}
		else if(line.find("x resolution") != std::string::npos)
		{
			std::getline(fs, line);
			displayResolution.x = std::stoi(line);
		} 
		else if(line.find("y resolution") != std::string::npos)
		{
			std::getline(fs, line);
			displayResolution.y = std::stoi(line);
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
	}

	fs.close();
}

void OptionsManager::writeMissingDefault()
{
	std::ofstream fs;
	fs.open(path.c_str(), std::ios::out | std::ios::app);
	if(fs.is_open())
	{
		if(internalResolution.x == 0)
		{
			internalResolution.x = defaultInternalResolution.x;
			fs << "x internalResolution = " << internalResolution.x << std::endl;
		}

		if(internalResolution.y == 0)
		{
			internalResolution.y = defaultInternalResolution.y;
			fs << "y internalResolution = " << internalResolution.y << std::endl;
		}

		if(displayResolution.x == 0)
		{
			displayResolution.x = defaultDisplayResolution.x;
			fs << "x resolution = " << displayResolution.x << std::endl;
		}

		if(displayResolution.y == 0)
		{
			displayResolution.y = defaultDisplayResolution.y; 
			fs << "y resolution = " << displayResolution.y << std::endl;
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

		fs.close();
	}
}

void OptionsManager::setDefault()
{
	displayResolution = defaultDisplayResolution;
	internalResolution = defaultInternalResolution;
	fullscreen = defaultFullscreen;
	vSync = defaultVSync;

	writeChanged();
}

void OptionsManager::writeChanged()
{
	std::ofstream fs;

	fs.open(path, std::ios::out | std::ios::trunc);

	if(fs.is_open())
	{
		fs << "x internalResolution = " << internalResolution.x << std::endl;

		fs << "y internalResolution = " << internalResolution.y << std::endl;

		fs << "x resolution = " << displayResolution.x << std::endl;

		fs << "y resolution = " << displayResolution.y << std::endl;

		fs << "fullscreen = " << fullscreen << std::endl;

		fs << "vsync = " << vSync << std::endl;

		fs.close();
	}
}

OptionsManager::~OptionsManager(void)
{
}
