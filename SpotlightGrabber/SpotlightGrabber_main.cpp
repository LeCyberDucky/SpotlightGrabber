#include <SFML\Graphics.hpp> //Using SFML 2.4.2

#include <algorithm>
#include <chrono>
#include <cstdint>
#include <filesystem>
#include <fstream>
#include <string>
#include <vector>

#include "GrabFunction.h"

int_fast32_t main()
{
	using sf::Image;
	using std::ofstream;		using std::getline;			 
	using std::string;

	namespace fs = std::experimental::filesystem;

	std::ifstream settingsFile;
	settingsFile.open("SpotlightSettings.txt");

	std::time_t currentTime{ std::chrono::system_clock::to_time_t(std::chrono::system_clock::now()) };

	string loadLocation, saveLocation, mobileSaveLoc, extension, lastRun;
	if(!getline(settingsFile, loadLocation))
	{
		ofstream errorLog;
		errorLog.open("ErrorLog - SpotlightGrabber.txt");
		errorLog << std::ctime(&currentTime) <<" - Failed at reading loadLocation\n";
		return 1;
	}
	if (!getline(settingsFile, saveLocation))
	{
		ofstream errorLog;
		errorLog.open("ErrorLog - SpotlightGrabber.txt");
		errorLog << std::ctime(&currentTime) << " - Failed at reading saveLocation\n";
		return 1;
	}
	if (!getline(settingsFile, mobileSaveLoc))
	{
		ofstream errorLog;
		errorLog.open("ErrorLog - SpotlightGrabber.txt");
		errorLog << std::ctime(&currentTime) << " - Failed at reading mobileSaveLocation\n";
		return 1;
	}
	if (!getline(settingsFile, extension))
	{
		ofstream errorLog;
		errorLog.open("ErrorLog - SpotlightGrabber.txt");
		errorLog << std::ctime(&currentTime) << " - Failed at reading extension\n";
		return 1;
	}
	if (!getline(settingsFile, lastRun))
	{
		ofstream errorLog;
		errorLog.open("ErrorLog - SpotlightGrabber.txt");
		errorLog << std::ctime(&currentTime) << " - Failed at reading time for last run\n";
		return 1;
	}

	//If difference between last run and now one day or more:
	int_fast64_t lastRunInt{ std::stoi(lastRun, 0) };
	if (currentTime - lastRunInt >= 84600)
		grabSpotlights(loadLocation, saveLocation, mobileSaveLoc, extension);

	//Rewrite file and lastRun
	settingsFile.close();
	std::ofstream settingsEdit;
	settingsEdit.open("SpotlightSettings.txt");
	settingsEdit << loadLocation << "\n" << saveLocation << "\n" << mobileSaveLoc << "\n" <<
					extension << "\n" << currentTime;
	
	return 0;
}