#pragma once
#include "FastWorldGenerator.h"
#include "generic/FormatConverter.h"
#include "generic/GenericModule.h"
#include "hoi4/Hoi4Parser.h"
#include "hoi4/Hoi4ScenarioGenerator.h"
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include <filesystem>
class Hoi4Module {
  // member variables
  Hoi4ScenarioGenerator hoi4Gen;
  int numCountries;
  std::string modName;
  std::string hoi4Path;
  std::string hoi4ModPath;
  std::string hoi4ModsDirectory;

public:
  Hoi4Module();
  ~Hoi4Module();
  // member functions
  // clear and create all the mod paths at each run
  bool createPaths();
  void genHoi(bool useDefaultMap, bool useDefaultStates,
              bool useDefaultProvinces, ScenarioGenerator &scenGen, bool cut);
  // try to locate hoi4 at configured path, if not found, try other standard
  // locations
  bool findHoi4();
  // read the config specific to hoi4
  void readConfig(std::string configSubFolder, std::string username);
};
