#include <SFML\Graphics.hpp>

#include <algorithm>
#include <cstdint>
#include <filesystem>
#include <fstream>
#include <string>
#include <vector>
#include "GrabFunction.h"

void grabSpotlights(std::string loadLocation, std::string saveLocation, std::string mobileSaveLocation, std::string extension)
{
	namespace fs = std::experimental::filesystem;

	std::vector<std::string> existingFiles;

	for (const auto& p : fs::directory_iterator(saveLocation))
	{
		existingFiles.emplace_back(p.path().stem().string());
	}

	for (const auto& p : fs::directory_iterator(mobileSaveLocation))
	{
		existingFiles.emplace_back(p.path().stem().string());
	}

	//Load every file that hasn't already been saved as image 
	//and check dimensions. If the dimensions fit -> copy and rename to save locations
	for (const auto& p : fs::directory_iterator(loadLocation))
	{
		if (std::find(existingFiles.cbegin(), existingFiles.cend(), p.path().stem().string()) == existingFiles.end())
		{
			sf::Image tempImg;
			tempImg.loadFromFile(p.path().string());

			if (tempImg.getSize().x % 16 == 0 && tempImg.getSize().y % 9 == 0)
			{
				fs::path copy{ saveLocation + "\\" + p.path().stem().string() + ".jpg" };
				fs::copy(p.path(), copy);
			}
			
			else if (tempImg.getSize().x % 9 == 0 && tempImg.getSize().y % 16 == 0)
			{
				fs::path copy{ mobileSaveLocation + "\\" + p.path().stem().string() + ".jpg" };
				fs::copy(p.path(), copy);
			}
		}
	}
}