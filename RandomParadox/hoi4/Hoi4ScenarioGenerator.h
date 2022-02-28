#pragma once
#include "../generic/countries/Country.h"
#include "../FastWorldGen/FastWorldGen/FastWorldGenerator.h"
#include "../generic/ScenarioGenerator.h"
#include "NationalFocus.h"
#include <set>



struct strategicRegion {
	std::set<int> gameRegionIDs;
	// weather: month{averageTemp, standard deviation, average precipitation, tempLow, tempHigh, tempNightly, snowChance, lightRainChance, heavyRainChance, blizzardChance,mudChance, sandstormChance}
	std::vector<std::vector<double>> weatherMonths;
	std::string name;
};


class Hoi4ScenarioGenerator
{
	std::ranlux24 random;
	// vars
	int landStates = 0;
	int focusID = 0;
	// vars - track industry statistics
	int totalWorldIndustry = 0;
	int militaryIndustry = 0;
	int navalIndustry = 0;
	int civilianIndustry = 0;
	// vars - track civil statistics
	long long worldPop = 0;
	// vars - track resource statistics
	int totalAluminium = 0;
	int totalChromium = 0;
	int totalRubber = 0;
	int totalOil = 0;
	int totalSteel = 0;
	int totalTungsten = 0;
	// containers
	std::vector<std::string> majorPowers;
	std::vector<std::string> regionalPowers;
	std::vector<std::string> weakPowers;
	std::vector<std::string> wargoalsAttack;
	std::vector<std::string> goalsDefence;
	std::map<std::string, NationalFocus::FocusType> typeMapping{
		{"attack", NationalFocus::FocusType::attack},
		{ "defense", NationalFocus::FocusType::defense },
		{ "ally", NationalFocus::FocusType::ally }
	};



public:

	// vars - config options
	double worldPopulationFactor = 1.0;
	double industryFactor = 1.0;
	double resourceFactor = 1.0;

	// containers
	std::vector<NationalFocus> foci;
	std::vector<NationalFocus> warFoci;
	std::map<int, std::vector<std::string>> strengthScores;
	// a list of connections: {sourceHub, destHub, provinces the rails go through}
	std::vector<std::vector<int>> supplyNodeConnections;
	// container holding the resource configurations
	std::map<std::string, std::vector<double>> resources;
	std::vector<strategicRegion> strategicRegions;

	// member functions
	// constructors/destructors
	Hoi4ScenarioGenerator();
	~Hoi4ScenarioGenerator();
	// give resources to states
	void generateStateResources(ScenarioGenerator& scenGen);
	// industry, development, population, state category
	void generateStateSpecifics(ScenarioGenerator& scenGen);
	// politics: ideology, strength, major
	void generateCountrySpecifics(ScenarioGenerator& scenGen, std::map<std::string, Country>& countries);
	// build strategic regions from gameregions
	void generateStrategicRegions(ScenarioGenerator& scenGen);
	// generate weather per strategic region, from baseprovinces
	void generateWeather(ScenarioGenerator& scenGen);
	// supply hubs and railroads
	void generateLogistics(ScenarioGenerator& scenGen);
	// calculate how strong each country is
	void evaluateCountries(ScenarioGenerator & scenGen);
	// determine unit composition, templates
	void generateCountryUnits(ScenarioGenerator & scenGen);
	// build a focus from the chain
	NationalFocus buildFocus(std::vector<std::string> chainStep, Country& source, Country& target);
	// make a tree out of all focus chains and single foci
	void buildFocusTree();
	// check if a national focus fulfills requirements
	bool fulfillsrequirements(std::vector<std::string> requirements, Country& source, Country& target);
	// evaluate the focus chains for each country
	void evaluateCountryGoals(ScenarioGenerator & scenGen);
	// see which countries are in need of unification
	void evaluateBrotherlyWars();
	// see which country needs to see some action
	void evaluateCivilWars();
	// create a strategy for this country
	void evaluateCountryStrategy();
	// print world info to console
	void printStatistics(ScenarioGenerator & scenGen);
};

