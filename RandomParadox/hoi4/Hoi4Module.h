#pragma once
#include "../FastWorldGen/FastWorldGen/FastWorldGenerator.h"
#include "../FormatConverter.h"
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include "Hoi4Parser.h"
//#include <filesystem>
#define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING
#include <experimental/filesystem>
#include "Hoi4ScenarioGenerator.h"
class Hoi4Module
{
	std::string hoi4Path;
	std::string hoi4ModPath;
public:
	Hoi4Module();
	~Hoi4Module();
	void createPaths();
	void genHoi(bool useDefaultMap, bool useDefaultStates, bool useDefaultProvinces, ScenarioGenerator& scenGen);

	void readConfig();
};

