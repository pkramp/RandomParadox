#include "generic/PdoxCountry.h"

PdoxCountry::PdoxCountry() : ID{-1} {}

PdoxCountry::PdoxCountry(std::string tag, int ID) : tag{tag}, ID{ID} {
  //auto random = Env::Instance().randNum;
  colour = {static_cast<unsigned char>(Env::Instance().randNum() % 255),
            static_cast<unsigned char>(Env::Instance().randNum() % 255),
            static_cast<unsigned char>(Env::Instance().randNum() % 255)};
}

PdoxCountry::~PdoxCountry() {}

void PdoxCountry::assignRegions(int maxRegions,
                            std::vector<GameRegion> &gameRegions,
                            GameRegion &startRegion,
                            std::vector<GameProvince> &gameProvinces) {
  addRegion(startRegion, gameRegions, gameProvinces);
  auto breakCounter = 0;
  while (ownedRegions.size() < maxRegions && breakCounter++ < 100) {
    for (const auto &gameRegion : ownedRegions) {
      if (ownedRegions.size() >= maxRegions)
        break;
      if (gameRegion.neighbours.size() == 0)
        continue;
      auto &nextRegion = UtilLib::selectRandom(gameRegion.neighbours);
      if (!gameRegions[nextRegion].assigned && !gameRegions[nextRegion].sea) {
        gameRegions[nextRegion].assigned = true;
        addRegion(gameRegions[nextRegion], gameRegions, gameProvinces);
      }
    }
  }
}

void PdoxCountry::addRegion(GameRegion &region,
                        std::vector<GameRegion> &gameRegions,
                        std::vector<GameProvince> &gameProvinces) {
  gameRegions[region.ID].assigned = true;
  gameRegions[region.ID].owner = tag;
  for (auto &gameProvince : gameRegions[region.ID].gameProvinces)
    gameProvince.owner = tag;
  region.assigned = true;
  region.owner = tag;
  for (auto &gameProvince : region.gameProvinces)
    gameProvince.owner = tag;
  ownedRegions.push_back(region);
}