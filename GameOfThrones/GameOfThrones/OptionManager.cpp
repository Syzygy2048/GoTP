#include "OptionManager.h"
#include <fstream>
#include <string>
#include <iostream>
#include <sys/stat.h>

OptionManager::OptionManager(void) : path("settings.txt"),defaultResolutionX(1280), defaultResolutionY(720), defaultFullscreen(false), defaultVSync(false)
{
	resolutionX = NULL;
	resolutionY = NULL;
	fullscreen = NULL;
	vSync = NULL;

	
	read();

	if(resolutionX == NULL || resolutionY == NULL || fullscreen == NULL || vSync == NULL)
		writeMissingDefault();

	changedResolutionX = resolutionX;
	changedResolutionY = resolutionY;
	changedFullscreen = fullscreen;
	changedVSync = vSync;
}


void OptionManager::read()
{

	std::ifstream fs;
	fs.open(path.c_str(), std::ios::in);
	if(!fs.is_open()) {
		std::cerr << "couldn't open filestream" << std::endl;
		return;
	}
	
	std::string line;
	
	//read line, check which setting it is and interpret it's value
	while (std::getline(fs, line, '='))
	{
		if(line.find("x resolution") != std::string::npos)
		{
			std::getline(fs, line);
			resolutionX = std::stoi(line);
		}
		else if(line.find("y resolution") != std::string::npos)
		{
			std::getline(fs, line);
			resolutionY = std::stoi(line);
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

void OptionManager::writeMissingDefault()
{
	std::ofstream fs;
	fs.open(path.c_str(), std::ios::out | std::ios::app);
	if(fs.is_open())
		{
		if(resolutionX == NULL)
		{
			resolutionX = defaultResolutionX;
			fs << "x resolution = " << defaultResolutionX << std::endl;
		}
		if(resolutionY == NULL)
		{
			resolutionY = defaultResolutionY;
			fs << "y resolution = " << defaultResolutionY << std::endl;
		}
		if(fullscreen == NULL)
		{
			fullscreen = defaultFullscreen;
			fs << "fullscreen = " << (defaultFullscreen ? 1 : 0) << std::endl; //can't easily cast bool to int
		}
		if(vSync == NULL)
		{
			vSync = defaultVSync;
			fs << "vsync = " << (defaultVSync ? 1 : 0) << std::endl;
		}
	
		fs.close();
	}
}

void OptionManager::setDefault()
{
	changedResolutionX = defaultResolutionX;
	changedResolutionY = defaultResolutionY;
	changedFullscreen = defaultFullscreen;
	changedVSync = defaultVSync;
}

void OptionManager::writeChanged()
{
	std::ofstream fs;
	fs.open(path, std::ios::out | std::ios::trunc);
	if(fs.is_open())
	{
		resolutionX = changedResolutionX;
		fs << "x resolution = " << changedResolutionX << std::endl;
		resolutionY = changedResolutionY;
		fs << "y resolution = " << changedResolutionY << std::endl;
		fullscreen = changedFullscreen;
		fs << "fullscreen = " << (changedFullscreen ? 1 : 0) << std::endl; //can't easily cast bool to int
		vSync = changedVSync;
		fs << "vsync = " << (changedVSync ? 1 : 0) << std::endl;

		fs.close();
	}
}

OptionManager::~OptionManager(void)
{
}
