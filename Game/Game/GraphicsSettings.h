#ifndef GRAPHICSSETTINGS_H
#define GRAPHICSSETTINGS_H

class GraphicsSettings
{
public:
	GraphicsSettings();

	string title;
	VideoMode resolution;
	bool fullscreen;
	bool verticalSync;
	unsigned frameRateLimit;
	ContextSettings contextSettings;
	vector<VideoMode> videoModes;

	void saveToflie(const string path);
	void loadFromFile(const string path);
};

#endif