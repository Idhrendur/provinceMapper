#include "Definitions.h"
#include "Log.h"
#include "OSCompatibilityLayer.h"
#include <fstream>
#include "../Provinces/Province.h"

void Definitions::loadDefinitions(std::istream& theStream)
{
	parseStream(theStream);
}

void Definitions::loadDefinitions(const std::string& fileName)
{
	if (!commonItems::DoesFileExist(fileName))
		throw std::runtime_error("Definitions file cannot be found!");

	std::ifstream definitionsFile(fileName);
	parseStream(definitionsFile);
	definitionsFile.close();
}

void Definitions::parseStream(std::istream& theStream)
{
	std::string line;
	getline(theStream, line); // discard first line.

	while (!theStream.eof())
	{
		getline(theStream, line);
		if (line[0] == '#' || line[1] == '#' || line.length() < 4)
			continue;

		auto province = std::make_shared<Province>();
		try
		{
			auto sepLoc = line.find(';');
			if (sepLoc == std::string::npos)
				continue;
			auto sepLocSave = sepLoc;
			province->ID = std::stoi(line.substr(0, sepLoc));
			sepLoc = line.find(';', sepLocSave + 1);
			if (sepLoc == std::string::npos)
				continue;
			province->r = std::stoi(line.substr(sepLocSave + 1, sepLoc - sepLocSave - 1));
			sepLocSave = sepLoc;
			sepLoc = line.find(';', sepLocSave + 1);
			if (sepLoc == std::string::npos)
				continue;
			province->g = std::stoi(line.substr(sepLocSave + 1, sepLoc - sepLocSave - 1));
			sepLocSave = sepLoc;
			sepLoc = line.find(';', sepLocSave + 1);
			if (sepLoc == std::string::npos)
				continue;
			province->b = std::stoi(line.substr(sepLocSave + 1, sepLoc - sepLocSave - 1));
			sepLocSave = sepLoc;
			sepLoc = line.find(';', sepLocSave + 1);
			if (sepLoc == std::string::npos)
				continue;
			province->mapDataName = line.substr(sepLocSave + 1, sepLoc - sepLocSave - 1);
		}
		catch (std::exception& e)
		{
			throw std::runtime_error("Line: |" + line + "| is unparseable! Breaking. (" + e.what() + ")");
		}
		
		provinces.insert(std::pair(province->ID, province));
	}
}
