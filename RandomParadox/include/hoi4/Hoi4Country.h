#pragma once
#include "Hoi4Region.h"
#include "NationalFocus.h"
#include "generic/PdoxCountry.h"
#include <array>
#include <string>
#include <vector>

namespace Scenario::Hoi4 {
class Hoi4Country : public Scenario::PdoxCountry {
public:
  enum class doctrineType {
    blitz,
    infantry,
    milita,
    artillery,
    armored,
    mass,
    support,
    defensive
  };
  Hoi4Country();
  Hoi4Country(Scenario::PdoxCountry &country, std::vector<Scenario::Region> &gameRegions);
  ~Hoi4Country();
  std::string fullName;
  std::string gfxCulture;
  std::string rank;
  std::string rulingParty;
  bool allowElections;
  double bully;
  double strengthScore;
  double relativeScore;
  // typedef doctrineType mytype;
  std::vector<doctrineType> doctrines;
  std::vector<int> units;
  std::vector<int> unitCount;
  std::array<int, 4> parties;
  std::vector<Region> hoi4Regions;
  std::vector<std::vector<NationalFocus>> foci;
};
} // namespace Scenario::Hoi4