#include "includeAll.h"
#include "GraphicsSettings.h"

GraphicsSettings::GraphicsSettings()
{
	this->title = "DEFAULT";
	this->resolution = VideoMode::getDesktopMode();
	this->fullscreen = false;
	this->verticalSync = false;
	this->frameRateLimit = 50;
	this->contextSettings.antialiasingLevel = 0;
	this->videoModes = VideoMode::getFullscreenModes();
}

void GraphicsSettings::saveToflie(const string path)
{
	ofstream ofs(path);

	if (ofs.is_open())
	{
		ofs << this->title << "\n";
		ofs << this->resolution.width << " " << this->resolution.height << "\n";
		ofs << this->fullscreen << "\n";
		ofs << this->frameRateLimit << "\n";
		ofs << this->verticalSync << "\n";
		ofs << this->contextSettings.antialiasingLevel;
	}

	ofs.close();
}

void GraphicsSettings::loadFromFile(const string path)
{
	ifstream ifs(path);

	if (ifs.is_open())
	{
		getline(ifs, this->title);
		ifs >> this->resolution.width >> this->resolution.height;
		ifs >> this->fullscreen;
		ifs >> this->frameRateLimit;
		ifs >> this->verticalSync;
		ifs >> this->contextSettings.antialiasingLevel;
	}

	ifs.close();
}