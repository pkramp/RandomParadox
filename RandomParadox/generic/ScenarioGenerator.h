#pragma once
#include "Countries/Country.h"
#include "../FastWorldGen/FastWorldGen/FastWorldGenerator.h"
#include "GameRegion.h"
#include "GameProvince.h"
#include "ResourceLoader.h"
#include "NameGenerator.h"
#include "Flag.h"
#include <map>
class ScenarioGenerator
{
	vector<Region> baseRegions;
	// used to gather data we don't want to generate ourselves
	ResourceLoader rLoader;
	std::map<std::string, Bitmap> bitmaps;
	std::map<std::string, std::string> gamePaths;
public:
	// generic vairables/containers used for every game
	FastWorldGenerator f;
	vector<Province*> provinces;
	vector<GameRegion> gameRegions;
	vector<GameProvince> gameProvinces;
	set<std::string> tags;
	map<std::string, Country> countryMap;

	NameGenerator nG;
	ScenarioGenerator(FastWorldGenerator& f);
	~ScenarioGenerator();

	void dumpDebugCountrymap(std::string path);
	// specific preparations. Used by each game, BUT to create game scenario
	void loadRequiredResources(std::string gamePath);

	// game specific preparations. Only used for specific games
	void hoi4Preparations(bool useDefaultStates, bool useDefaultProvinces);

	// generic preparations. However, if desired, there are necessary preparations for every game
	// such as reading in the existing worldmap, states, regions, provinces etc
	void generateWorld();
	// map base regions to generic paradox compatible game regions
	void mapRegions();
	// map base provinces to generic paradox compatible game provinces
	void mapProvinces();
	//void generateReligions(); // not for hoi4

	void generatePopulations();
	void generateDevelopment();

	// GameRegions are used for every single game,
	GameRegion& findStartRegion();
	// and countries are always created the same way
	void generateCountries();
};

